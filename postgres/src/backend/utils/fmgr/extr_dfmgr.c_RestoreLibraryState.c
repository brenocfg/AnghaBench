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
 int /*<<< orphan*/  internal_load_library (char*) ; 
 scalar_t__ strlen (char*) ; 

void
RestoreLibraryState(char *start_address)
{
	while (*start_address != '\0')
	{
		internal_load_library(start_address);
		start_address += strlen(start_address) + 1;
	}
}