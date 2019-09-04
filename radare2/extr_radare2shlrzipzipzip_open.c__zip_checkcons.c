#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zip_uint64_t ;
typedef  int zip_int64_t ;
struct zip_error {int dummy; } ;
struct zip_dirent {int /*<<< orphan*/ * extra_fields; } ;
struct zip_cdir {size_t nentry; TYPE_1__* entry; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {size_t offset; size_t comp_size; int local_extra_fields_read; int /*<<< orphan*/  extra_fields; int /*<<< orphan*/  filename; } ;
struct TYPE_3__ {TYPE_2__* orig; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LENTRYSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  ZIP_ER_INCONS ; 
 int /*<<< orphan*/  ZIP_ER_NOZIP ; 
 int /*<<< orphan*/  ZIP_ER_SEEK ; 
 size_t ZIP_INT64_MAX ; 
 int /*<<< orphan*/  _zip_dirent_finalize (struct zip_dirent*) ; 
 int _zip_dirent_read (struct zip_dirent*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct zip_error*) ; 
 int /*<<< orphan*/  _zip_ef_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _zip_headercomp (TYPE_2__*,struct zip_dirent*) ; 
 size_t _zip_string_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zip_int64_t
_zip_checkcons(FILE *fp, struct zip_cdir *cd, struct zip_error *error)
{
    zip_uint64_t i;
    zip_uint64_t min, max, j;
    struct zip_dirent temp;

    if (cd->nentry) {
	max = cd->entry[0].orig->offset;
	min = cd->entry[0].orig->offset;
    }
    else
	min = max = 0;

    for (i=0; i<cd->nentry; i++) {
	if (cd->entry[i].orig->offset < min)
	    min = cd->entry[i].orig->offset;
	if (min > (zip_uint64_t)cd->offset) {
	    _zip_error_set(error, ZIP_ER_NOZIP, 0);
	    return -1;
	}
	
	j = cd->entry[i].orig->offset + cd->entry[i].orig->comp_size
	    + _zip_string_length(cd->entry[i].orig->filename) + LENTRYSIZE;
	if (j > max)
	    max = j;
	if (max > (zip_uint64_t)cd->offset) {
	    _zip_error_set(error, ZIP_ER_NOZIP, 0);
	    return -1;
	}
	
	if (fseeko(fp, (off_t)cd->entry[i].orig->offset, SEEK_SET) != 0) {
	    _zip_error_set(error, ZIP_ER_SEEK, errno);
	    return -1;
	}
	
	if (_zip_dirent_read(&temp, fp, NULL, NULL, 1, error) == -1)
	    return -1;
	
	if (_zip_headercomp(cd->entry[i].orig, &temp) != 0) {
	    _zip_error_set(error, ZIP_ER_INCONS, 0);
	    _zip_dirent_finalize(&temp);
	    return -1;
	}
	
	cd->entry[i].orig->extra_fields = _zip_ef_merge(cd->entry[i].orig->extra_fields, temp.extra_fields);
	cd->entry[i].orig->local_extra_fields_read = 1;
	temp.extra_fields = NULL;
	
	_zip_dirent_finalize(&temp);
    }

    return (max-min) < ZIP_INT64_MAX ? (zip_int64_t)(max-min) : ZIP_INT64_MAX;
}