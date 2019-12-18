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
struct dstr {int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int recursive_mkdir (int /*<<< orphan*/ ) ; 

int os_mkdirs(const char *dir)
{
	struct dstr dir_str;
	int ret;

	dstr_init_copy(&dir_str, dir);
	dstr_replace(&dir_str, "\\", "/");
	ret = recursive_mkdir(dir_str.array);
	dstr_free(&dir_str);
	return ret;
}