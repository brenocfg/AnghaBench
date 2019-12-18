#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* source; } ;
typedef  TYPE_3__ obs_scene_t ;
typedef  int /*<<< orphan*/  calldata_t ;
struct TYPE_6__ {int /*<<< orphan*/  signals; } ;
struct TYPE_7__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_set_ptr (int /*<<< orphan*/ *,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void signal_parent(obs_scene_t *parent, const char *command,
			  calldata_t *params)
{
	calldata_set_ptr(params, "scene", parent);
	signal_handler_signal(parent->source->context.signals, command, params);
}