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

/* Variables and functions */
 int ADI_MAX_VERSION ; 
 int /*<<< orphan*/  RDTICK (long) ; 

__attribute__((used)) static int random_version(void)
{
	long tick;

	RDTICK(tick);

	return tick % (ADI_MAX_VERSION + 1);
}