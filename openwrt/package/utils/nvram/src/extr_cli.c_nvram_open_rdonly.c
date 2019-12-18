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
 int /*<<< orphan*/  NVRAM_RO ; 
 int /*<<< orphan*/  NVRAM_STAGING ; 
 int /*<<< orphan*/  free (char*) ; 
 char* nvram_find_mtd () ; 
 char* nvram_find_staging () ; 
 int /*<<< orphan*/ * nvram_open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nvram_handle_t * nvram_open_rdonly(void)
{
	char *file = nvram_find_staging();

	if( file == NULL )
		file = nvram_find_mtd();

	if( file != NULL ) {
		nvram_handle_t *h = nvram_open(file, NVRAM_RO);
		if( strcmp(file, NVRAM_STAGING) )
			free(file);
		return h;
	}

	return NULL;
}