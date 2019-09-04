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
struct lapb_cb {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  lapb_hold (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __lapb_insert_cb(struct lapb_cb *lapb)
{
	list_add(&lapb->node, &lapb_list);
	lapb_hold(lapb);
}