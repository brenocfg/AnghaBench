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
struct mp_tags {int num_keys; int /*<<< orphan*/ * values; int /*<<< orphan*/ * keys; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ bstrcasecmp0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

void mp_tags_remove_bstr(struct mp_tags *tags, bstr key)
{
    for (int n = 0; n < tags->num_keys; n++) {
        if (bstrcasecmp0(key, tags->keys[n]) == 0) {
            talloc_free(tags->keys[n]);
            talloc_free(tags->values[n]);
            int num_keys = tags->num_keys; // copy so it's only decremented once
            MP_TARRAY_REMOVE_AT(tags->keys, num_keys, n);
            MP_TARRAY_REMOVE_AT(tags->values, tags->num_keys, n);
        }
    }
}