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
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 scalar_t__ calldata_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  twitch_ingests_refresh (int) ; 

__attribute__((used)) static void refresh_callback(void *unused, calldata_t *cd)
{
	int seconds = (int)calldata_int(cd, "seconds");
	if (seconds <= 0)
		seconds = 3;
	if (seconds > 10)
		seconds = 10;

	twitch_ingests_refresh(seconds);

	UNUSED_PARAMETER(unused);
}