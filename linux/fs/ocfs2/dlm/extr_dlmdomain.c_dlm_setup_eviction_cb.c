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
struct dlm_eviction_cb {void* ec_data; int /*<<< orphan*/ * ec_func; int /*<<< orphan*/  ec_item; } ;
typedef  int /*<<< orphan*/  dlm_eviction_func ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void dlm_setup_eviction_cb(struct dlm_eviction_cb *cb,
			   dlm_eviction_func *f,
			   void *data)
{
	INIT_LIST_HEAD(&cb->ec_item);
	cb->ec_func = f;
	cb->ec_data = data;
}