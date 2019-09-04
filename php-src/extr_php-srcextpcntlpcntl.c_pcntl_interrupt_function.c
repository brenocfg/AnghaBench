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
typedef  int /*<<< orphan*/  zend_execute_data ;

/* Variables and functions */
 int /*<<< orphan*/  orig_interrupt_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcntl_signal_dispatch () ; 

__attribute__((used)) static void pcntl_interrupt_function(zend_execute_data *execute_data)
{
	pcntl_signal_dispatch();
	if (orig_interrupt_function) {
		orig_interrupt_function(execute_data);
	}
}