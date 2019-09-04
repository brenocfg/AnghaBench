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
typedef  int /*<<< orphan*/  zip_uint64_t ;
typedef  int /*<<< orphan*/  zip_int64_t ;
typedef  scalar_t__ uLong ;
struct zip_filelist {int dummy; } ;
struct zip {int /*<<< orphan*/  error; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TORRENT_CRC_LEN ; 
 int /*<<< orphan*/  ZIP_AFL_TORRENT ; 
 int /*<<< orphan*/  ZIP_ER_SEEK ; 
 int /*<<< orphan*/  ZIP_ER_WRITE ; 
 int /*<<< orphan*/  _zip_cdir_write (struct zip*,struct zip_filelist const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _zip_filerange_crc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long) ; 
 scalar_t__ zip_get_archive_flag (struct zip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_cdir(struct zip *za, const struct zip_filelist *filelist, zip_uint64_t survivors, FILE *out)
{
    off_t cd_start, end;
    zip_int64_t size;
    uLong crc;
    char buf[TORRENT_CRC_LEN+1];

    cd_start = ftello(out);
	if (cd_start < 0)
		return -1;

    if ((size=_zip_cdir_write(za, filelist, survivors, out)) < 0)
	return -1;
    
    end = ftello(out);

    if (zip_get_archive_flag(za, ZIP_AFL_TORRENT, 0) == 0)
	return 0;


    /* fix up torrentzip comment */

    if (_zip_filerange_crc(out, cd_start, size, &crc, &za->error) < 0)
	return -1;

    snprintf(buf, sizeof(buf), "%08lX", (long)crc);

    if (fseeko(out, end-TORRENT_CRC_LEN, SEEK_SET) < 0) {
	_zip_error_set(&za->error, ZIP_ER_SEEK, errno);
	return -1;
    }

    if (fwrite(buf, TORRENT_CRC_LEN, 1, out) != 1) {
	_zip_error_set(&za->error, ZIP_ER_WRITE, errno);
	return -1;
    }

    return 0;
}