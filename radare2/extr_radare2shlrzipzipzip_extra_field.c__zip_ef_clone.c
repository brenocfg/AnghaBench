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
struct zip_extra_field {struct zip_extra_field* next; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  size; int /*<<< orphan*/  id; } ;
struct zip_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_ef_free (struct zip_extra_field*) ; 
 struct zip_extra_field* _zip_ef_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct zip_extra_field *
_zip_ef_clone(const struct zip_extra_field *ef, struct zip_error *error)
{
    struct zip_extra_field *head, *prev, *def;
    
    head = prev = NULL;
    
    while (ef) {
        if ((def=_zip_ef_new(ef->id, ef->size, ef->data, ef->flags)) == NULL) {
            _zip_error_set(error, ZIP_ER_MEMORY, 0);
            _zip_ef_free(head);
            return NULL;
        }
        
        if (head == NULL)
            head = def;
        if (prev)
            prev->next = def;
        prev = def;

	ef = ef->next;
    }
    
    return head;
}