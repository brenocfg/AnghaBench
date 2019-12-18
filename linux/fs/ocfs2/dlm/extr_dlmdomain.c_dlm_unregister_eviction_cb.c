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
struct dlm_eviction_cb {int /*<<< orphan*/  ec_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_callback_sem ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void dlm_unregister_eviction_cb(struct dlm_eviction_cb *cb)
{
	down_write(&dlm_callback_sem);
	list_del_init(&cb->ec_item);
	up_write(&dlm_callback_sem);
}