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
struct hda_vmaster_mute_hook {int mute_mode; int /*<<< orphan*/  codec; int /*<<< orphan*/  (* hook ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int HDA_VMUTE_FOLLOW_MASTER ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vmaster_hook(void *private_data, int enabled)
{
	struct hda_vmaster_mute_hook *hook = private_data;

	if (hook->mute_mode != HDA_VMUTE_FOLLOW_MASTER)
		enabled = hook->mute_mode;
	hook->hook(hook->codec, enabled);
}