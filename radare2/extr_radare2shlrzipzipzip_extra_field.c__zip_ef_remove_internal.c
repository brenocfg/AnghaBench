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
struct zip_extra_field {struct zip_extra_field* next; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ ZIP_EF_IS_INTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_ef_free (struct zip_extra_field*) ; 

struct zip_extra_field *
_zip_ef_remove_internal(struct zip_extra_field *ef)
{
    struct zip_extra_field *ef_head;
    struct zip_extra_field *prev, *next;
    
    ef_head = ef;
    prev = NULL;
    
    while (ef) {
        if (ZIP_EF_IS_INTERNAL(ef->id)) {
            next = ef->next;
            if (ef_head == ef)
                ef_head = next;
            ef->next = NULL;
            _zip_ef_free(ef);
            if (prev)
                prev->next = next;
            ef = next;
        }
        else {
            prev = ef;
            ef = ef->next;
        }
    }
    
    return ef_head;
}