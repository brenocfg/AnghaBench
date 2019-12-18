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
 int /*<<< orphan*/  croak (char*) ; 
 scalar_t__ plperl_ending ; 

__attribute__((used)) static void
check_spi_usage_allowed(void)
{
	/* see comment in plperl_fini() */
	if (plperl_ending)
	{
		/* simple croak as we don't want to involve PostgreSQL code */
		croak("SPI functions can not be used in END blocks");
	}
}