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
typedef  scalar_t__ zip_uint64_t ;
struct zip_error {int dummy; } ;
struct zip_cdir {void* offset; void* size; } ;
typedef  void* off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFBIG ; 
 int EOCDLEN ; 
 unsigned int ZIP_CHECKCONS ; 
 int /*<<< orphan*/  ZIP_ER_INCONS ; 
 int /*<<< orphan*/  ZIP_ER_NOZIP ; 
 int /*<<< orphan*/  ZIP_ER_SEEK ; 
 scalar_t__ ZIP_OFF_MAX ; 
 struct zip_cdir* _zip_cdir_new (scalar_t__,struct zip_error*) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _zip_read2 (unsigned char const**) ; 
 scalar_t__ _zip_read4 (unsigned char const**) ; 

__attribute__((used)) static struct zip_cdir *
_zip_read_eocd(const unsigned char *eocd, const unsigned char *buf, off_t buf_offset, size_t buflen,
	       unsigned int flags, struct zip_error *error)
{
    struct zip_cdir *cd;
    const unsigned char *cdp;
    zip_uint64_t i, nentry, size, offset;

    if (eocd+EOCDLEN > buf+buflen) {
	_zip_error_set(error, ZIP_ER_INCONS, 0);
	return NULL;
    }

    cdp = eocd + 8;

    /* number of cdir-entries on this disk */
    i = _zip_read2(&cdp);
    /* number of cdir-entries */
    nentry = _zip_read2(&cdp);

    if (nentry != i) {
	_zip_error_set(error, ZIP_ER_NOZIP, 0);
	return NULL;
    }

    size = _zip_read4(&cdp);
    offset = _zip_read4(&cdp);

    if (size > ZIP_OFF_MAX || offset > ZIP_OFF_MAX || offset+size > ZIP_OFF_MAX) {
        _zip_error_set(error, ZIP_ER_SEEK, EFBIG);
        return NULL;
    }
    
    if (offset+size > (zip_uint64_t)(buf_offset + (eocd-buf))) {
	/* cdir spans past EOCD record */
	_zip_error_set(error, ZIP_ER_INCONS, 0);
	return NULL;
    }

    if ((flags & ZIP_CHECKCONS) && offset+size != (zip_uint64_t)(buf_offset + (eocd-buf))) {
	_zip_error_set(error, ZIP_ER_INCONS, 0);
	return NULL;
    }

    if ((cd=_zip_cdir_new(nentry, error)) == NULL)
	return NULL;

    cd->size = (off_t)size;
    cd->offset = (off_t)offset;
    
    return cd;
}