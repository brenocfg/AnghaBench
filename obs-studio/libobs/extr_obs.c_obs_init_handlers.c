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
struct TYPE_2__ {int /*<<< orphan*/  signals; int /*<<< orphan*/  procs; } ;

/* Variables and functions */
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_signals ; 
 int /*<<< orphan*/  proc_handler_create () ; 
 int signal_handler_add_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler_create () ; 

__attribute__((used)) static inline bool obs_init_handlers(void)
{
	obs->signals = signal_handler_create();
	if (!obs->signals)
		return false;

	obs->procs = proc_handler_create();
	if (!obs->procs)
		return false;

	return signal_handler_add_array(obs->signals, obs_signals);
}