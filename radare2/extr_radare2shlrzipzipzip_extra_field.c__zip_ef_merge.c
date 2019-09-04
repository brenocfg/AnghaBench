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
struct zip_extra_field {scalar_t__ id; scalar_t__ size; int flags; struct zip_extra_field* next; scalar_t__ data; } ;

/* Variables and functions */
 int ZIP_EF_BOTH ; 
 int /*<<< orphan*/  _zip_ef_free (struct zip_extra_field*) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,scalar_t__,scalar_t__) ; 

struct zip_extra_field *
_zip_ef_merge(struct zip_extra_field *to, struct zip_extra_field *from)
{
    struct zip_extra_field *ef2, *tt, *tail;
    int duplicate;

    if (to == NULL)
	return from;

    for (tail=to; tail->next; tail=tail->next)
	;

    for (; from; from=ef2) {
	ef2 = from->next;

	duplicate = 0;
	for (tt=to; tt; tt=tt->next) {
	    if (tt->id == from->id && tt->size == from->size) {
		if (tt->data && from->data && !memcmp(tt->data, from->data, tt->size)) {
			tt->flags |= (from->flags & ZIP_EF_BOTH);
			duplicate = 1;
			break;
		}
	    }
	}

	from->next = NULL;
	if (duplicate)
	    _zip_ef_free(from);
	else
	    tail = tail->next = from;
    }

    return to;
}