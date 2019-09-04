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
typedef  int /*<<< orphan*/  zip_uint8_t ;
typedef  int zip_uint16_t ;
typedef  int /*<<< orphan*/  zip_flags_t ;
struct zip_extra_field {struct zip_extra_field* next; } ;
struct zip_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_INCONS ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_ef_free (struct zip_extra_field*) ; 
 struct zip_extra_field* _zip_ef_new (int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _zip_read2 (int /*<<< orphan*/  const**) ; 

struct zip_extra_field *
_zip_ef_parse(const zip_uint8_t *data, zip_uint16_t len, zip_flags_t flags, struct zip_error *error)
{
    struct zip_extra_field *ef, *ef2, *ef_head;
    const zip_uint8_t *p;
    zip_uint16_t fid, flen;

    ef_head = NULL;
    for (p=data; p<data+len; p+=flen) {
	if (p+4 > data+len) {
	    _zip_error_set(error, ZIP_ER_INCONS, 0);
	    _zip_ef_free(ef_head);
	    return NULL;
	}

	fid = _zip_read2(&p);
	flen = _zip_read2(&p);

	if (p+flen > data+len) {
	    _zip_error_set(error, ZIP_ER_INCONS, 0);
	    _zip_ef_free(ef_head);
	    return NULL;
	}

	if ((ef2=_zip_ef_new(fid, flen, p, flags)) == NULL) {
	    _zip_error_set(error, ZIP_ER_MEMORY, 0);
	    _zip_ef_free(ef_head);
	    return NULL;
	}

	if (ef_head) {
	    ef->next = ef2;
	    ef = ef2;
	}
	else
	    ef_head = ef = ef2;
    }

    return ef_head;
}