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
typedef  size_t zip_uint64_t ;
typedef  size_t zip_uint32_t ;
typedef  size_t zip_uint16_t ;
typedef  int zip_int64_t ;
struct zip_string {size_t length; int /*<<< orphan*/  raw; } ;
struct zip_filelist {int idx; } ;
struct zip_entry {scalar_t__ orig; scalar_t__ changes; } ;
struct zip {int /*<<< orphan*/  error; struct zip_string* comment_orig; struct zip_string* comment_changes; scalar_t__ comment_changed; struct zip_entry* entry; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOCD64LEN ; 
 int /*<<< orphan*/  EOCD64LOC_MAGIC ; 
 int /*<<< orphan*/  EOCD64_MAGIC ; 
 int /*<<< orphan*/  EOCD_MAGIC ; 
 int /*<<< orphan*/  ZIP_ER_READ ; 
 int /*<<< orphan*/  ZIP_ER_WRITE ; 
 int /*<<< orphan*/  ZIP_FL_CENTRAL ; 
 size_t ZIP_UINT16_MAX ; 
 size_t ZIP_UINT32_MAX ; 
 int _zip_dirent_write (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_write2 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_write4 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_write8 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

zip_int64_t
_zip_cdir_write(struct zip *za, const struct zip_filelist *filelist, zip_uint64_t survivors, FILE *fp)
{
    off_t off;
    zip_uint64_t offset, size;
    struct zip_string *comment;
    zip_uint64_t i;
    int is_zip64;
    int ret;

    if ((off=ftello(fp)) < 0) {
        _zip_error_set(&za->error, ZIP_ER_READ, errno);
        return -1;
    }
    offset = (zip_uint64_t)off;

    is_zip64 = 0;

    for (i=0; i<survivors; i++) {
	struct zip_entry *entry = za->entry+filelist[i].idx;

	if ((ret=_zip_dirent_write(entry->changes ? entry->changes : entry->orig, fp, ZIP_FL_CENTRAL, &za->error)) < 0)
	    return -1;
	if (ret)
	    is_zip64 = 1;
    }

    if ((off=ftello(fp)) < 0) {
        _zip_error_set(&za->error, ZIP_ER_READ, errno);
        return -1;
    }
    size = (zip_uint64_t)off - offset;

    if (offset > ZIP_UINT32_MAX || survivors > ZIP_UINT16_MAX)
	is_zip64 = 1;

    if (is_zip64) {
	fwrite(EOCD64_MAGIC, 1, 4, fp);
	_zip_write8(EOCD64LEN-12, fp);
	_zip_write2(45, fp);
	_zip_write2(45, fp);
	_zip_write4(0, fp);
	_zip_write4(0, fp);
	_zip_write8(survivors, fp);
	_zip_write8(survivors, fp);
	_zip_write8(size, fp);
	_zip_write8(offset, fp);

	fwrite(EOCD64LOC_MAGIC, 1, 4, fp);
	_zip_write4(0, fp);
	_zip_write8(offset+size, fp);
	_zip_write4(1, fp);
		    
    }

    /* clearerr(fp); */
    fwrite(EOCD_MAGIC, 1, 4, fp);
    _zip_write4(0, fp);
    _zip_write2(survivors >= ZIP_UINT16_MAX ? ZIP_UINT16_MAX : (zip_uint16_t)survivors, fp);
    _zip_write2(survivors >= ZIP_UINT16_MAX ? ZIP_UINT16_MAX : (zip_uint16_t)survivors, fp);
    _zip_write4(size >= ZIP_UINT32_MAX ? ZIP_UINT32_MAX : (zip_uint32_t)size, fp);
    _zip_write4(offset >= ZIP_UINT32_MAX ? ZIP_UINT32_MAX : (zip_uint32_t)offset, fp);

    comment = za->comment_changed ? za->comment_changes : za->comment_orig;

    _zip_write2(comment ? comment->length : 0, fp);
    if (comment)
	fwrite(comment->raw, 1, comment->length, fp);

    if (ferror(fp)) {
	_zip_error_set(&za->error, ZIP_ER_WRITE, errno);
	return -1;
    }

    return (zip_int64_t)size;
}