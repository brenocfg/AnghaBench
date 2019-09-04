#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  user; TYPE_1__* handler; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RAnalEsilInterrupt ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _interrupt_free_cb(void *user) {
	RAnalEsilInterrupt *intr = (RAnalEsilInterrupt *)user;
	if (intr && intr->handler && intr->handler->fini) {
		intr->handler->fini (intr->user);
	}
	free (intr);
}