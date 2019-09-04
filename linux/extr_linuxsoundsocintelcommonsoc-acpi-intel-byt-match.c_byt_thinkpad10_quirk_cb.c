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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_THINKPAD_10 ; 
 int /*<<< orphan*/  byt_machine_id ; 

__attribute__((used)) static int byt_thinkpad10_quirk_cb(const struct dmi_system_id *id)
{
	byt_machine_id = BYT_THINKPAD_10;
	return 1;
}