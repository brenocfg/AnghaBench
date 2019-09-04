#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fc_seq {int dummy; } ;
struct fc_frame_header {scalar_t__ ct_explan; int /*<<< orphan*/  ct_cmd; int /*<<< orphan*/  ct_reason; int /*<<< orphan*/  fh_seq_cnt; } ;
struct fc_frame {int dummy; } ;
struct fc_disc {unsigned int seq_count; int /*<<< orphan*/  disc_mutex; } ;
struct fc_ct_hdr {scalar_t__ ct_explan; int /*<<< orphan*/  ct_cmd; int /*<<< orphan*/  ct_reason; int /*<<< orphan*/  fh_seq_cnt; } ;
typedef  enum fc_disc_event { ____Placeholder_fc_disc_event } fc_disc_event ;

/* Variables and functions */
 int DISC_EV_FAILED ; 
 int DISC_EV_NONE ; 
 int DISC_EV_SUCCESS ; 
 struct fc_frame* ERR_PTR (int) ; 
 int /*<<< orphan*/  FC_DISC_DBG (struct fc_disc*,char*,...) ; 
 unsigned int FC_FS_ACC ; 
 scalar_t__ FC_FS_EXP_FTNR ; 
 unsigned int FC_FS_RJT ; 
 int /*<<< orphan*/  FC_FS_RJT_UNABL ; 
 scalar_t__ FC_SOF_I3 ; 
 scalar_t__ FC_SOF_N3 ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fc_disc_done (struct fc_disc*,int) ; 
 int /*<<< orphan*/  fc_disc_error (struct fc_disc*,struct fc_frame*) ; 
 int fc_disc_gpn_ft_parse (struct fc_disc*,struct fc_frame_header*,unsigned int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_is_linear (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fr_eof (struct fc_frame*) ; 
 int fr_len (struct fc_frame*) ; 
 scalar_t__ fr_sof (struct fc_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_disc_gpn_ft_resp(struct fc_seq *sp, struct fc_frame *fp,
				void *disc_arg)
{
	struct fc_disc *disc = disc_arg;
	struct fc_ct_hdr *cp;
	struct fc_frame_header *fh;
	enum fc_disc_event event = DISC_EV_NONE;
	unsigned int seq_cnt;
	unsigned int len;
	int error = 0;

	mutex_lock(&disc->disc_mutex);
	FC_DISC_DBG(disc, "Received a GPN_FT response\n");

	if (IS_ERR(fp)) {
		fc_disc_error(disc, fp);
		mutex_unlock(&disc->disc_mutex);
		return;
	}

	WARN_ON(!fc_frame_is_linear(fp));	/* buffer must be contiguous */
	fh = fc_frame_header_get(fp);
	len = fr_len(fp) - sizeof(*fh);
	seq_cnt = ntohs(fh->fh_seq_cnt);
	if (fr_sof(fp) == FC_SOF_I3 && seq_cnt == 0 && disc->seq_count == 0) {
		cp = fc_frame_payload_get(fp, sizeof(*cp));
		if (!cp) {
			FC_DISC_DBG(disc, "GPN_FT response too short, len %d\n",
				    fr_len(fp));
			event = DISC_EV_FAILED;
		} else if (ntohs(cp->ct_cmd) == FC_FS_ACC) {

			/* Accepted, parse the response. */
			len -= sizeof(*cp);
			error = fc_disc_gpn_ft_parse(disc, cp + 1, len);
		} else if (ntohs(cp->ct_cmd) == FC_FS_RJT) {
			FC_DISC_DBG(disc, "GPN_FT rejected reason %x exp %x "
				    "(check zoning)\n", cp->ct_reason,
				    cp->ct_explan);
			event = DISC_EV_FAILED;
			if (cp->ct_reason == FC_FS_RJT_UNABL &&
			    cp->ct_explan == FC_FS_EXP_FTNR)
				event = DISC_EV_SUCCESS;
		} else {
			FC_DISC_DBG(disc, "GPN_FT unexpected response code "
				    "%x\n", ntohs(cp->ct_cmd));
			event = DISC_EV_FAILED;
		}
	} else if (fr_sof(fp) == FC_SOF_N3 && seq_cnt == disc->seq_count) {
		error = fc_disc_gpn_ft_parse(disc, fh + 1, len);
	} else {
		FC_DISC_DBG(disc, "GPN_FT unexpected frame - out of sequence? "
			    "seq_cnt %x expected %x sof %x eof %x\n",
			    seq_cnt, disc->seq_count, fr_sof(fp), fr_eof(fp));
		event = DISC_EV_FAILED;
	}
	if (error)
		fc_disc_error(disc, ERR_PTR(error));
	else if (event != DISC_EV_NONE)
		fc_disc_done(disc, event);
	fc_frame_free(fp);
	mutex_unlock(&disc->disc_mutex);
}