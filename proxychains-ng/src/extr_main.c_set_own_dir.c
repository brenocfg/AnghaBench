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
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 scalar_t__* own_dir ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void set_own_dir(const char *argv0) {
	size_t l = strlen(argv0);
	while(l && argv0[l - 1] != '/')
		l--;
	if(l == 0)
#ifdef SUPER_SECURE
		memcpy(own_dir, "/dev/null/", 11);
#else
		memcpy(own_dir, ".", 2);
#endif
	else {
		memcpy(own_dir, argv0, l - 1);
		own_dir[l] = 0;
	}
}