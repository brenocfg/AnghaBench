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
typedef  int /*<<< orphan*/  signal_handler_t ;
typedef  int /*<<< orphan*/  signal_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  signal_handler_connect_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int) ; 

void signal_handler_connect(signal_handler_t *handler, const char *signal,
			    signal_callback_t callback, void *data)
{
	signal_handler_connect_internal(handler, signal, callback, data, false);
}