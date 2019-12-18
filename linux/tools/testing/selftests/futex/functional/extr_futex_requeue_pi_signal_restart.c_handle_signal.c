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
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,char*) ; 
 TYPE_1__ requeued ; 

void handle_signal(int signo)
{
	info("signal received %s requeue\n",
	     requeued.val ? "after" : "prior to");
}