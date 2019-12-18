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
 scalar_t__ do_main () ; 
 int foo_main () ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char **argv) {
	if (argc>1) {
		printf ("grubfs api\n");
		return foo_main ();
	}
	printf ("grub internal api\n");
	if (do_main()) {
		printf ("\n** worked!\n");
	} else {
		printf ("\n** failed!\n");
	}
	return 0;
}