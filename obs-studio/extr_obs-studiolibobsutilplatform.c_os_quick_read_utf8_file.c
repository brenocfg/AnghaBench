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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_fopen (char const*,char*) ; 
 int /*<<< orphan*/  os_fread_utf8 (int /*<<< orphan*/ *,char**) ; 

char *os_quick_read_utf8_file(const char *path)
{
	FILE *f = os_fopen(path, "rb");
	char *file_string = NULL;

	if (!f)
		return NULL;

	os_fread_utf8(f, &file_string);
	fclose(f);

	return file_string;
}