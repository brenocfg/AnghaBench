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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ os_file_exists (char const*) ; 

int os_copyfile(const char *file_path_in, const char *file_path_out)
{
	FILE *file_out = NULL;
	FILE *file_in = NULL;
	uint8_t data[4096];
	int ret = -1;
	size_t size;

	if (os_file_exists(file_path_out))
		return -1;

	file_in = fopen(file_path_in, "rb");
	if (!file_in)
		return -1;

	file_out = fopen(file_path_out, "ab+");
	if (!file_out)
		goto error;

	do {
		size = fread(data, 1, sizeof(data), file_in);
		if (size)
			size = fwrite(data, 1, size, file_out);
	} while (size == sizeof(data));

	ret = feof(file_in) ? 0 : -1;

error:
	if (file_out)
		fclose(file_out);
	fclose(file_in);
	return ret;
}