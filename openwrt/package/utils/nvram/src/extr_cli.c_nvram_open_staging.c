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
typedef  int /*<<< orphan*/  nvram_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVRAM_RW ; 
 int /*<<< orphan*/  NVRAM_STAGING ; 
 int /*<<< orphan*/ * nvram_find_staging () ; 
 int /*<<< orphan*/ * nvram_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvram_to_staging () ; 

__attribute__((used)) static nvram_handle_t * nvram_open_staging(void)
{
	if( nvram_find_staging() != NULL || nvram_to_staging() == 0 )
		return nvram_open(NVRAM_STAGING, NVRAM_RW);

	return NULL;
}