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
struct async {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct async*) ; 
 struct async* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct async *alloc_async(unsigned int numisoframes)
{
	struct async *as;

	as = kzalloc(sizeof(struct async), GFP_KERNEL);
	if (!as)
		return NULL;
	as->urb = usb_alloc_urb(numisoframes, GFP_KERNEL);
	if (!as->urb) {
		kfree(as);
		return NULL;
	}
	return as;
}