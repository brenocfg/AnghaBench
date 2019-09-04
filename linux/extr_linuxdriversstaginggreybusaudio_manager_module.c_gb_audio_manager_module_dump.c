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
struct TYPE_2__ {int /*<<< orphan*/  op_devices; int /*<<< orphan*/  ip_devices; int /*<<< orphan*/  intf_id; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; int /*<<< orphan*/  name; } ;
struct gb_audio_manager_module {TYPE_1__ desc; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gb_audio_manager_module_dump(struct gb_audio_manager_module *module)
{
	pr_info("audio module #%d name=%s vid=%d pid=%d intf_id=%d i/p devices=0x%X o/p devices=0x%X\n",
		module->id,
		module->desc.name,
		module->desc.vid,
		module->desc.pid,
		module->desc.intf_id,
		module->desc.ip_devices,
		module->desc.op_devices);
}