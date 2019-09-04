#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct AdapterControlBlock {TYPE_1__ eternal_timer; int /*<<< orphan*/  fw_flag; int /*<<< orphan*/  ante_token_value; int /*<<< orphan*/  rq_map_token; int /*<<< orphan*/  arcmsr_do_message_isr_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_NORMAL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  arcmsr_message_isr_bh_fn ; 
 int /*<<< orphan*/  arcmsr_request_device_map ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_init_get_devmap_timer(struct AdapterControlBlock *pacb)
{
	INIT_WORK(&pacb->arcmsr_do_message_isr_bh, arcmsr_message_isr_bh_fn);
	atomic_set(&pacb->rq_map_token, 16);
	atomic_set(&pacb->ante_token_value, 16);
	pacb->fw_flag = FW_NORMAL;
	timer_setup(&pacb->eternal_timer, arcmsr_request_device_map, 0);
	pacb->eternal_timer.expires = jiffies + msecs_to_jiffies(6 * HZ);
	add_timer(&pacb->eternal_timer);
}