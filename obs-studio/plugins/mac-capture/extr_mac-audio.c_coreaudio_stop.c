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
struct coreaudio_data {int active; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioOutputUnitStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_success (int /*<<< orphan*/ ,struct coreaudio_data*,char*,char*) ; 

__attribute__((used)) static void coreaudio_stop(struct coreaudio_data *ca)
{
	OSStatus stat;

	if (!ca->active)
		return;

	ca->active = false;

	stat = AudioOutputUnitStop(ca->unit);
	ca_success(stat, ca, "coreaudio_stop", "stop audio");
}