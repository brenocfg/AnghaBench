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
typedef  int /*<<< orphan*/  va_list ;
struct kobject {char const* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 char* kvasprintf_const (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strreplace (char*,char,char) ; 

int kobject_set_name_vargs(struct kobject *kobj, const char *fmt,
				  va_list vargs)
{
	const char *s;

	if (kobj->name && !fmt)
		return 0;

	s = kvasprintf_const(GFP_KERNEL, fmt, vargs);
	if (!s)
		return -ENOMEM;

	/*
	 * ewww... some of these buggers have '/' in the name ... If
	 * that's the case, we need to make sure we have an actual
	 * allocated copy to modify, since kvasprintf_const may have
	 * returned something from .rodata.
	 */
	if (strchr(s, '/')) {
		char *t;

		t = kstrdup(s, GFP_KERNEL);
		kfree_const(s);
		if (!t)
			return -ENOMEM;
		strreplace(t, '/', '!');
		s = t;
	}
	kfree_const(kobj->name);
	kobj->name = s;

	return 0;
}