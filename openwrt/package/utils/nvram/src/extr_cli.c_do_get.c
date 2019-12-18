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
 char* nvram_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int do_get(nvram_handle_t *nvram, const char *var)
{
	const char *val;
	int stat = 1;

	if( (val = nvram_get(nvram, var)) != NULL )
	{
		printf("%s\n", val);
		stat = 0;
	}

	return stat;
}