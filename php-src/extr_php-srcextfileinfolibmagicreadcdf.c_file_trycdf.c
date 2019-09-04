#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;

/* Type definitions */
struct magic_set {int flags; } ;
struct buffer {int fd; unsigned char* fbuf; size_t flen; } ;
struct TYPE_44__ {int sst_len; int sst_ss; int /*<<< orphan*/ * sst_tab; } ;
typedef  TYPE_1__ cdf_stream_t ;
struct TYPE_45__ {int /*<<< orphan*/  sat_tab; } ;
typedef  TYPE_2__ cdf_sat_t ;
struct TYPE_46__ {int i_fd; unsigned char const* i_buf; size_t i_len; } ;
typedef  TYPE_3__ cdf_info_t ;
typedef  int /*<<< orphan*/  cdf_header_t ;
typedef  int /*<<< orphan*/  cdf_directory_t ;
struct TYPE_47__ {int /*<<< orphan*/  dir_tab; } ;
typedef  TYPE_4__ cdf_dir_t ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int MAGIC_APPLE ; 
 int MAGIC_EXTENSION ; 
 scalar_t__ NOTMIME (struct magic_set*) ; 
 int cdf_check_summary_info (struct magic_set*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_4__*,TYPE_1__*,int /*<<< orphan*/  const*,char const**) ; 
 int cdf_file_dir_info (struct magic_set*,TYPE_4__*) ; 
 int cdf_read_dir (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*) ; 
 int cdf_read_doc_summary_info (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_4__*,TYPE_1__*) ; 
 int cdf_read_header (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int cdf_read_sat (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int cdf_read_short_stream (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*,TYPE_1__*,int /*<<< orphan*/  const**) ; 
 int cdf_read_ssat (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int cdf_read_summary_info (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_4__*,TYPE_1__*) ; 
 int cdf_read_user_stream (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_1__*,TYPE_4__*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdf_zero_stream (TYPE_1__*) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int file_printf (struct magic_set*,char*,...) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 

int
file_trycdf(struct magic_set *ms, const struct buffer *b)
{
	int fd = b->fd;
	const unsigned char *buf = b->fbuf;
	size_t nbytes = b->flen;
        cdf_info_t info;
        cdf_header_t h;
        cdf_sat_t sat, ssat;
        cdf_stream_t sst, scn;
        cdf_dir_t dir;
        int i;
        const char *expn = "";
        const cdf_directory_t *root_storage;

        scn.sst_tab = NULL;
        info.i_fd = fd;
        info.i_buf = buf;
        info.i_len = nbytes;
        if (ms->flags & (MAGIC_APPLE|MAGIC_EXTENSION))
                return 0;
        if (cdf_read_header(&info, &h) == -1)
                return 0;
#ifdef CDF_DEBUG
        cdf_dump_header(&h);
#endif

        if ((i = cdf_read_sat(&info, &h, &sat)) == -1) {
                expn = "Can't read SAT";
                goto out0;
        }
#ifdef CDF_DEBUG
        cdf_dump_sat("SAT", &sat, CDF_SEC_SIZE(&h));
#endif

        if ((i = cdf_read_ssat(&info, &h, &sat, &ssat)) == -1) {
                expn = "Can't read SSAT";
                goto out1;
        }
#ifdef CDF_DEBUG
        cdf_dump_sat("SSAT", &ssat, CDF_SHORT_SEC_SIZE(&h));
#endif

        if ((i = cdf_read_dir(&info, &h, &sat, &dir)) == -1) {
                expn = "Can't read directory";
                goto out2;
        }

        if ((i = cdf_read_short_stream(&info, &h, &sat, &dir, &sst,
	    &root_storage)) == -1) {
                expn = "Cannot read short stream";
                goto out3;
        }
#ifdef CDF_DEBUG
        cdf_dump_dir(&info, &h, &sat, &ssat, &sst, &dir);
#endif
#ifdef notdef
	if (root_storage) {
		if (NOTMIME(ms)) {
			char clsbuf[128];
			if (file_printf(ms, "CLSID %s, ",
			    format_clsid(clsbuf, sizeof(clsbuf),
			    root_storage->d_storage_uuid)) == -1)
				return -1;
		}
	}
#endif

	if ((i = cdf_read_user_stream(&info, &h, &sat, &ssat, &sst, &dir,
	    "FileHeader", &scn)) != -1) {
#define HWP5_SIGNATURE "HWP Document File"
		if (scn.sst_len * scn.sst_ss >= sizeof(HWP5_SIGNATURE) - 1
		    && memcmp(scn.sst_tab, HWP5_SIGNATURE,
		    sizeof(HWP5_SIGNATURE) - 1) == 0) {
		    if (NOTMIME(ms)) {
			if (file_printf(ms,
			    "Hangul (Korean) Word Processor File 5.x") == -1)
			    return -1;
		    } else {
			if (file_printf(ms, "application/x-hwp") == -1)
			    return -1;
		    }
		    i = 1;
		    goto out5;
		} else {
		    cdf_zero_stream(&scn);
		}
	}

        if ((i = cdf_read_summary_info(&info, &h, &sat, &ssat, &sst, &dir,
            &scn)) == -1) {
                if (errno != ESRCH) {
                        expn = "Cannot read summary info";
		}
	} else {
		i = cdf_check_summary_info(ms, &info, &h,
		    &sat, &ssat, &sst, &dir, &scn, root_storage, &expn);
		cdf_zero_stream(&scn);
	}
	if (i <= 0) {
		if ((i = cdf_read_doc_summary_info(&info, &h, &sat, &ssat,
		    &sst, &dir, &scn)) == -1) {
			if (errno != ESRCH) {
				expn = "Cannot read summary info";
			}
		} else {
			i = cdf_check_summary_info(ms, &info, &h, &sat, &ssat,
			    &sst, &dir, &scn, root_storage, &expn);
		}
	}
	if (i <= 0) {
		i = cdf_file_dir_info(ms, &dir);
		if (i < 0)
			expn = "Cannot read section info";
	}
out5:
	cdf_zero_stream(&scn);
	cdf_zero_stream(&sst);
out3:
        efree(dir.dir_tab);
out2:
        efree(ssat.sat_tab);
out1:
        efree(sat.sat_tab);
out0:
	if (i == -1) {
	    if (NOTMIME(ms)) {
		if (file_printf(ms,
		    "Composite Document File V2 Document") == -1)
		    return -1;
		if (*expn)
		    if (file_printf(ms, ", %s", expn) == -1)
			return -1;
	    } else {
		if (file_printf(ms, "application/CDFV2") == -1)
		    return -1;
	    }
	    i = 1;
	}
        return i;
}