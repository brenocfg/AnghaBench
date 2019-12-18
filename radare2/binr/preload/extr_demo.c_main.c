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
 int /*<<< orphan*/  RTLD_LAZY ; 
 void* dlopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 

int main(int argc, char **argv) {
	void *a = dlopen(NULL, RTLD_LAZY);
	void *m = dlsym (a, "r_main_radare2");
	if (m) {
		int (*r2main)(int argc, char **argv) = m;
		return r2main (argc, argv);
	}
	return 0;
}