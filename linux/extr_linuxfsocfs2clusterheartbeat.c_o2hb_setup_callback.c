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
struct o2hb_callback_func {int hc_priority; int hc_type; int /*<<< orphan*/  hc_magic; void* hc_data; int /*<<< orphan*/ * hc_func; int /*<<< orphan*/  hc_item; } ;
typedef  int /*<<< orphan*/  o2hb_cb_func ;
typedef  enum o2hb_callback_type { ____Placeholder_o2hb_callback_type } o2hb_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O2HB_CB_MAGIC ; 

void o2hb_setup_callback(struct o2hb_callback_func *hc,
			 enum o2hb_callback_type type,
			 o2hb_cb_func *func,
			 void *data,
			 int priority)
{
	INIT_LIST_HEAD(&hc->hc_item);
	hc->hc_func = func;
	hc->hc_data = data;
	hc->hc_priority = priority;
	hc->hc_type = type;
	hc->hc_magic = O2HB_CB_MAGIC;
}