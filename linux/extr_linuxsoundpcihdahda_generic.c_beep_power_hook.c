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
struct hda_beep {int /*<<< orphan*/  nid; int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_path_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void beep_power_hook(struct hda_beep *beep, bool on)
{
	set_path_power(beep->codec, beep->nid, -1, on);
}