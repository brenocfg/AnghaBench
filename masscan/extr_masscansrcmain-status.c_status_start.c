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
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  time; int /*<<< orphan*/  clock; } ;
struct Status {int timer; TYPE_1__ last; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock () ; 
 int /*<<< orphan*/  memset (struct Status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void
status_start(struct Status *status)
{
    memset(status, 0, sizeof(*status));
    status->last.clock = clock();
    status->last.time = time(0);
    status->last.count = 0;
    status->timer = 0x1;
}