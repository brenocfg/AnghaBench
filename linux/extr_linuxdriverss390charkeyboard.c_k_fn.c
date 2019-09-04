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
struct kbd_data {scalar_t__* func_table; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kbd_puts_queue (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
k_fn(struct kbd_data *kbd, unsigned char value)
{
	if (kbd->func_table[value])
		kbd_puts_queue(kbd->port, kbd->func_table[value]);
}