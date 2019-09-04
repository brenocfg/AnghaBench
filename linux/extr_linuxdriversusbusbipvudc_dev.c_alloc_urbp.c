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
struct urbp {int /*<<< orphan*/  urb_entry; int /*<<< orphan*/ * ep; int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct urbp* kzalloc (int,int /*<<< orphan*/ ) ; 

struct urbp *alloc_urbp(void)
{
	struct urbp *urb_p;

	urb_p = kzalloc(sizeof(*urb_p), GFP_KERNEL);
	if (!urb_p)
		return urb_p;

	urb_p->urb = NULL;
	urb_p->ep = NULL;
	INIT_LIST_HEAD(&urb_p->urb_entry);
	return urb_p;
}