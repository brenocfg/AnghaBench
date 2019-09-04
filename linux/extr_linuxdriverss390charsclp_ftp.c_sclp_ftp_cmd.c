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
struct hmcdrv_ftp_cmdspec {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 scalar_t__ EIO ; 
 scalar_t__ ENOENT ; 
 scalar_t__ EPERM ; 
#define  SCLP_DIAG_FTP_LDFAIL 131 
#define  SCLP_DIAG_FTP_LDNPERM 130 
#define  SCLP_DIAG_FTP_LDRUNS 129 
#define  SCLP_DIAG_FTP_OK 128 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ sclp_ftp_et7 (struct hmcdrv_ftp_cmdspec const*) ; 
 size_t sclp_ftp_fsize ; 
 int sclp_ftp_ldflg ; 
 scalar_t__ sclp_ftp_length ; 
 int /*<<< orphan*/  sclp_ftp_rx_complete ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

ssize_t sclp_ftp_cmd(const struct hmcdrv_ftp_cmdspec *ftp, size_t *fsize)
{
	ssize_t len;
#ifdef DEBUG
	unsigned long start_jiffies;

	pr_debug("starting SCLP (ET7), cmd %d for '%s' at %lld with %zd bytes\n",
		 ftp->id, ftp->fname, (long long) ftp->ofs, ftp->len);
	start_jiffies = jiffies;
#endif

	init_completion(&sclp_ftp_rx_complete);

	/* Start ftp sclp command. */
	len = sclp_ftp_et7(ftp);
	if (len)
		goto out_unlock;

	/*
	 * There is no way to cancel the sclp ET7 request, the code
	 * needs to wait unconditionally until the transfer is complete.
	 */
	wait_for_completion(&sclp_ftp_rx_complete);

#ifdef DEBUG
	pr_debug("completed SCLP (ET7) request after %lu ms (all)\n",
		 (jiffies - start_jiffies) * 1000 / HZ);
	pr_debug("return code of SCLP (ET7) FTP Service is 0x%02x, with %lld/%lld bytes\n",
		 sclp_ftp_ldflg, sclp_ftp_length, sclp_ftp_fsize);
#endif

	switch (sclp_ftp_ldflg) {
	case SCLP_DIAG_FTP_OK:
		len = sclp_ftp_length;
		if (fsize)
			*fsize = sclp_ftp_fsize;
		break;
	case SCLP_DIAG_FTP_LDNPERM:
		len = -EPERM;
		break;
	case SCLP_DIAG_FTP_LDRUNS:
		len = -EBUSY;
		break;
	case SCLP_DIAG_FTP_LDFAIL:
		len = -ENOENT;
		break;
	default:
		len = -EIO;
		break;
	}

out_unlock:
	return len;
}