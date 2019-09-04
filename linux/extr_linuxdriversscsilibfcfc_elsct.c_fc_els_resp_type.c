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
struct fc_frame_header {int fh_type; } ;
struct fc_frame {int dummy; } ;
struct fc_ct_hdr {int /*<<< orphan*/  ct_cmd; } ;

/* Variables and functions */
#define  ELS_LS_ACC 136 
#define  ELS_LS_RJT 135 
#define  FC_EX_CLOSED 134 
#define  FC_EX_TIMEOUT 133 
#define  FC_FS_ACC 132 
#define  FC_FS_RJT 131 
#define  FC_NO_ERR 130 
#define  FC_TYPE_CT 129 
#define  FC_TYPE_ELS 128 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int PTR_ERR (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fc_ct_hdr* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

const char *fc_els_resp_type(struct fc_frame *fp)
{
	const char *msg;
	struct fc_frame_header *fh;
	struct fc_ct_hdr *ct;

	if (IS_ERR(fp)) {
		switch (-PTR_ERR(fp)) {
		case FC_NO_ERR:
			msg = "response no error";
			break;
		case FC_EX_TIMEOUT:
			msg = "response timeout";
			break;
		case FC_EX_CLOSED:
			msg = "response closed";
			break;
		default:
			msg = "response unknown error";
			break;
		}
	} else {
		fh = fc_frame_header_get(fp);
		switch (fh->fh_type) {
		case FC_TYPE_ELS:
			switch (fc_frame_payload_op(fp)) {
			case ELS_LS_ACC:
				msg = "accept";
				break;
			case ELS_LS_RJT:
				msg = "reject";
				break;
			default:
				msg = "response unknown ELS";
				break;
			}
			break;
		case FC_TYPE_CT:
			ct = fc_frame_payload_get(fp, sizeof(*ct));
			if (ct) {
				switch (ntohs(ct->ct_cmd)) {
				case FC_FS_ACC:
					msg = "CT accept";
					break;
				case FC_FS_RJT:
					msg = "CT reject";
					break;
				default:
					msg = "response unknown CT";
					break;
				}
			} else {
				msg = "short CT response";
			}
			break;
		default:
			msg = "response not ELS or CT";
			break;
		}
	}
	return msg;
}