#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ signal_handler_t ;

/* Variables and functions */
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_actually_destroy (TYPE_1__*) ; 

void signal_handler_destroy(signal_handler_t *handler)
{
	if (handler && os_atomic_dec_long(&handler->refs) == 0) {
		signal_handler_actually_destroy(handler);
	}
}