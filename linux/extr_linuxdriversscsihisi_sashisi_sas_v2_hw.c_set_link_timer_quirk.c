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
struct TYPE_2__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct hisi_hba {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  link_timeout_disable_link ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static void set_link_timer_quirk(struct hisi_hba *hisi_hba)
{
	hisi_hba->timer.function = link_timeout_disable_link;
	hisi_hba->timer.expires = jiffies + msecs_to_jiffies(1000);
	add_timer(&hisi_hba->timer);
}