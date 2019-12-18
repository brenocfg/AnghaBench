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
struct script_callback {int /*<<< orphan*/  extra; } ;
typedef  int /*<<< orphan*/  signal_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calldata_ptr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  calldata_signal_callback ; 
 char* calldata_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  signal_handler_connect (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct script_callback*) ; 

__attribute__((used)) static void defer_connect(void *p_cb)
{
	struct script_callback *cb = p_cb;

	signal_handler_t *handler = calldata_ptr(&cb->extra, "handler");
	const char *signal = calldata_string(&cb->extra, "signal");
	signal_handler_connect(handler, signal, calldata_signal_callback, cb);
}