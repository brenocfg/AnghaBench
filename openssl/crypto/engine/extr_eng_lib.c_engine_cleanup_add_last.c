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
typedef  int /*<<< orphan*/  ENGINE_CLEANUP_ITEM ;
typedef  int /*<<< orphan*/  ENGINE_CLEANUP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_stack ; 
 int /*<<< orphan*/  int_cleanup_check (int) ; 
 int /*<<< orphan*/ * int_cleanup_item (int /*<<< orphan*/ *) ; 
 scalar_t__ sk_ENGINE_CLEANUP_ITEM_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void engine_cleanup_add_last(ENGINE_CLEANUP_CB *cb)
{
    ENGINE_CLEANUP_ITEM *item;
    if (!int_cleanup_check(1))
        return;
    item = int_cleanup_item(cb);
    if (item != NULL) {
        if (sk_ENGINE_CLEANUP_ITEM_push(cleanup_stack, item) <= 0)
            OPENSSL_free(item);
    }
}