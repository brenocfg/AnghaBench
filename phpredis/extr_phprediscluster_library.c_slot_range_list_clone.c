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
typedef  int /*<<< orphan*/  zend_llist ;
typedef  int /*<<< orphan*/  redisSlotRange ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pemalloc (size_t,int) ; 
 size_t zend_llist_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_llist_get_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_llist_get_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static redisSlotRange *slot_range_list_clone(zend_llist *src, size_t *count) {
    redisSlotRange *dst, *range;
    size_t i = 0;

    *count = zend_llist_count(src);
    dst = pemalloc(*count * sizeof(*dst), 1);

    range = zend_llist_get_first(src);
    while (range) {
        memcpy(&dst[i++], range, sizeof(*range));
        range = zend_llist_get_next(src);
     }

    return dst;
}