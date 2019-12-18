#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/  calldata_t ;
struct TYPE_3__ {int /*<<< orphan*/  signals; } ;
struct TYPE_4__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calldata_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calldata_set_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hotkey_signal(const char *signal, obs_hotkey_t *hotkey)
{
	calldata_t data;
	calldata_init(&data);
	calldata_set_ptr(&data, "key", hotkey);

	signal_handler_signal(obs->hotkeys.signals, signal, &data);

	calldata_free(&data);
}