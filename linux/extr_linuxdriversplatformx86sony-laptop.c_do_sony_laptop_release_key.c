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
struct timer_list {int dummy; } ;
struct sony_laptop_keypress {int /*<<< orphan*/  dev; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  kp ;
struct TYPE_2__ {int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  release_key_timer; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ kfifo_len (int /*<<< orphan*/ *) ; 
 int kfifo_out (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 TYPE_1__ sony_laptop_input ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void do_sony_laptop_release_key(struct timer_list *unused)
{
	struct sony_laptop_keypress kp;
	unsigned long flags;

	spin_lock_irqsave(&sony_laptop_input.fifo_lock, flags);

	if (kfifo_out(&sony_laptop_input.fifo,
		      (unsigned char *)&kp, sizeof(kp)) == sizeof(kp)) {
		input_report_key(kp.dev, kp.key, 0);
		input_sync(kp.dev);
	}

	/* If there is something in the fifo schedule next release. */
	if (kfifo_len(&sony_laptop_input.fifo) != 0)
		mod_timer(&sony_laptop_input.release_key_timer,
			  jiffies + msecs_to_jiffies(10));

	spin_unlock_irqrestore(&sony_laptop_input.fifo_lock, flags);
}