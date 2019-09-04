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
struct dstr {char* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 char* strrchr (char*,char) ; 

const char *os_get_path_extension(const char *path)
{
	struct dstr temp;
	size_t pos = 0;
	char *period;
	char *slash;

	dstr_init_copy(&temp, path);
	dstr_replace(&temp, "\\", "/");

	slash = strrchr(temp.array, '/');
	period = strrchr(temp.array, '.');
	if (period)
		pos = (size_t)(period - temp.array);

	dstr_free(&temp);

	if (!period || slash > period)
		return NULL;

	return path + pos;
}