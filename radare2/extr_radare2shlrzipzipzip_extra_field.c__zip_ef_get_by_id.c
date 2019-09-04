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
typedef  char zip_uint8_t ;
typedef  scalar_t__ zip_uint16_t ;
typedef  int zip_flags_t ;
struct zip_extra_field {scalar_t__ id; int flags; scalar_t__ size; char const* data; struct zip_extra_field* next; } ;
struct zip_error {int dummy; } ;

/* Variables and functions */
 int ZIP_EF_BOTH ; 
 int /*<<< orphan*/  ZIP_ER_NOENT ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const zip_uint8_t *
_zip_ef_get_by_id(const struct zip_extra_field *ef, zip_uint16_t *lenp, zip_uint16_t id, zip_uint16_t id_idx, zip_flags_t flags, struct zip_error *error)
{
    static const zip_uint8_t empty[1] = { '\0' };
    
    int i;

    i = 0;
    for (; ef; ef=ef->next) {
	if (ef->id == id && (ef->flags & flags & ZIP_EF_BOTH)) {
	    if (i < id_idx) {
		i++;
		continue;
	    }

	    if (lenp)
		*lenp = ef->size;
	    if (ef->size > 0)
		return ef->data;
	    else
		return empty;
	}
    }

    _zip_error_set(error, ZIP_ER_NOENT, 0);
    return NULL;
}