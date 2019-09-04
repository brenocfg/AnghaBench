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
struct urbp {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_urbp (struct urbp*) ; 

void free_urbp_and_urb(struct urbp *urb_p)
{
	if (!urb_p)
		return;
	free_urb(urb_p->urb);
	free_urbp(urb_p);
}