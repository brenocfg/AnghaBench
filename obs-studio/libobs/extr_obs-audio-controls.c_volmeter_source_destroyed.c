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
struct obs_volmeter {int dummy; } ;
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_volmeter_detach_source (struct obs_volmeter*) ; 

__attribute__((used)) static void volmeter_source_destroyed(void *vptr, calldata_t *calldata)
{
	UNUSED_PARAMETER(calldata);
	struct obs_volmeter *volmeter = (struct obs_volmeter *)vptr;

	obs_volmeter_detach_source(volmeter);
}