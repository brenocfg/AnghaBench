#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  head; int /*<<< orphan*/  tail; } ;
struct io_rings {TYPE_1__ cq; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static unsigned io_cqring_events(struct io_rings *rings)
{
	/* See comment at the top of this file */
	smp_rmb();
	return READ_ONCE(rings->cq.tail) - READ_ONCE(rings->cq.head);
}