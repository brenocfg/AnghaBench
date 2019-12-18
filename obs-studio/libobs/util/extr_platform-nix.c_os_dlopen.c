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
 int /*<<< orphan*/  LOG_ERROR ; 
 int RTLD_FIRST ; 
 int RTLD_LAZY ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlerror () ; 
 void* dlopen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_find (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 

void *os_dlopen(const char *path)
{
	struct dstr dylib_name;

	if (!path)
		return NULL;

	dstr_init_copy(&dylib_name, path);
#ifdef __APPLE__
	if (!dstr_find(&dylib_name, ".so") && !dstr_find(&dylib_name, ".dylib"))
#else
	if (!dstr_find(&dylib_name, ".so"))
#endif
		dstr_cat(&dylib_name, ".so");

#ifdef __APPLE__
	void *res = dlopen(dylib_name.array, RTLD_LAZY | RTLD_FIRST);
#else
	void *res = dlopen(dylib_name.array, RTLD_LAZY);
#endif
	if (!res)
		blog(LOG_ERROR, "os_dlopen(%s->%s): %s\n", path,
		     dylib_name.array, dlerror());

	dstr_free(&dylib_name);
	return res;
}