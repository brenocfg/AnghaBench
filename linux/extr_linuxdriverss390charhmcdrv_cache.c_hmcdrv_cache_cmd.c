#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hmcdrv_ftp_cmdspec {scalar_t__ id; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ (* hmcdrv_cache_ftpfunc ) (struct hmcdrv_ftp_cmdspec const*,int /*<<< orphan*/ *) ;
struct TYPE_2__ {int ofs; int /*<<< orphan*/  fsize; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ HMCDRV_FTP_DIR ; 
 scalar_t__ HMCDRV_FTP_GET ; 
 scalar_t__ HMCDRV_FTP_NLIST ; 
 int /*<<< orphan*/  HMCDRV_FTP_NOOP ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 scalar_t__ hmcdrv_cache_do (struct hmcdrv_ftp_cmdspec const*,scalar_t__ (*) (struct hmcdrv_ftp_cmdspec const*,int /*<<< orphan*/ *)) ; 
 TYPE_1__ hmcdrv_cache_file ; 
 scalar_t__ hmcdrv_cache_get (struct hmcdrv_ftp_cmdspec const*) ; 

ssize_t hmcdrv_cache_cmd(const struct hmcdrv_ftp_cmdspec *ftp,
			 hmcdrv_cache_ftpfunc func)
{
	ssize_t len;

	if ((ftp->id == HMCDRV_FTP_DIR) || /* read cache */
	    (ftp->id == HMCDRV_FTP_NLIST) ||
	    (ftp->id == HMCDRV_FTP_GET)) {

		len = hmcdrv_cache_get(ftp);

		if (len >= 0) /* got it from cache ? */
			return len; /* yes */

		len = hmcdrv_cache_do(ftp, func);

		if (len >= 0)
			return len;

	} else {
		len = func(ftp, NULL); /* simply do original command */
	}

	/* invalidate the (read) cache in case there was a write operation
	 * or an error on read/dir
	 */
	hmcdrv_cache_file.id = HMCDRV_FTP_NOOP;
	hmcdrv_cache_file.fsize = LLONG_MAX;
	hmcdrv_cache_file.ofs = -1;

	return len;
}