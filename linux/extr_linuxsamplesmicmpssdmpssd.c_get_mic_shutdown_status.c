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
struct mic_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MIC_CRASHED ; 
 int MIC_HALTED ; 
 int MIC_NOP ; 
 int MIC_POWER_OFF ; 
 int MIC_RESTART ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
get_mic_shutdown_status(struct mic_info *mic, char *shutdown_status)
{
	if (!strcmp(shutdown_status, "nop"))
		return MIC_NOP;
	if (!strcmp(shutdown_status, "crashed"))
		return MIC_CRASHED;
	if (!strcmp(shutdown_status, "halted"))
		return MIC_HALTED;
	if (!strcmp(shutdown_status, "poweroff"))
		return MIC_POWER_OFF;
	if (!strcmp(shutdown_status, "restart"))
		return MIC_RESTART;
	mpsslog("%s: BUG invalid status %s\n", mic->name, shutdown_status);
	/* Invalid state */
	assert(0);
}