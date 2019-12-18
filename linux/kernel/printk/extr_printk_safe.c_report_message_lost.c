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
struct printk_safe_seq_buf {int /*<<< orphan*/  message_lost; } ;

/* Variables and functions */
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_deferred (char*,int) ; 

__attribute__((used)) static void report_message_lost(struct printk_safe_seq_buf *s)
{
	int lost = atomic_xchg(&s->message_lost, 0);

	if (lost)
		printk_deferred("Lost %d message(s)!\n", lost);
}