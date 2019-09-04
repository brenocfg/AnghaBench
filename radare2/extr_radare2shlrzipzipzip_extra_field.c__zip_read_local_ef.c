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
typedef  int /*<<< orphan*/  zip_uint8_t ;
typedef  scalar_t__ zip_uint64_t ;
typedef  scalar_t__ zip_uint16_t ;
struct zip_extra_field {int dummy; } ;
struct zip_entry {TYPE_2__* changes; TYPE_1__* orig; } ;
struct zip {scalar_t__ nentry; int /*<<< orphan*/  error; int /*<<< orphan*/  zp; struct zip_entry* entry; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_4__ {int local_extra_fields_read; int /*<<< orphan*/  extra_fields; } ;
struct TYPE_3__ {int local_extra_fields_read; int /*<<< orphan*/  extra_fields; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  ZIP_EF_LOCAL ; 
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
 int /*<<< orphan*/  ZIP_ER_READ ; 
 int /*<<< orphan*/  ZIP_ER_SEEK ; 
 int /*<<< orphan*/  _zip_ef_merge (int /*<<< orphan*/ ,struct zip_extra_field*) ; 
 struct zip_extra_field* _zip_ef_parse (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct zip_extra_field* _zip_ef_remove_internal (struct zip_extra_field*) ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _zip_read2 (unsigned char const**) ; 
 int /*<<< orphan*/ * _zip_read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_zip_read_local_ef(struct zip *za, zip_uint64_t idx)
{
    struct zip_entry *e;
    unsigned char b[4];
    const unsigned char *p;
    zip_uint16_t fname_len, ef_len;

    if (idx >= za->nentry) {
	_zip_error_set(&za->error, ZIP_ER_INVAL, 0);
	return -1;
    }

    e = za->entry+idx;

    if (e->orig == NULL || e->orig->local_extra_fields_read)
	return 0;


    if (fseeko(za->zp, (off_t)(e->orig->offset + 26), SEEK_SET) < 0) {
	_zip_error_set(&za->error, ZIP_ER_SEEK, errno);
	return -1;
    }

    if (fread(b, sizeof(b), 1, za->zp) != 1) {
	_zip_error_set(&za->error, ZIP_ER_READ, errno);
	return -1;
    }

    p = b;
    fname_len = _zip_read2(&p);
    ef_len = _zip_read2(&p);

    if (ef_len > 0) {
	struct zip_extra_field *ef;
	zip_uint8_t *ef_raw;

	if (fseek(za->zp, fname_len, SEEK_CUR) < 0) {
	    _zip_error_set(&za->error, ZIP_ER_SEEK, errno);
	    return -1;
	}

	ef_raw = _zip_read_data(NULL, za->zp, ef_len, 0, &za->error);

	if (ef_raw == NULL)
	    return -1;

	if ((ef=_zip_ef_parse(ef_raw, ef_len, ZIP_EF_LOCAL, &za->error)) == NULL) {
	    free(ef_raw);
	    return -1;
	}
	free(ef_raw);
	
        ef = _zip_ef_remove_internal(ef);
	e->orig->extra_fields = _zip_ef_merge(e->orig->extra_fields, ef);
    }

    e->orig->local_extra_fields_read = 1;
    
    if (e->changes && e->changes->local_extra_fields_read == 0) {
	e->changes->extra_fields = e->orig->extra_fields;
	e->changes->local_extra_fields_read = 1;
    }

    return 0;
}