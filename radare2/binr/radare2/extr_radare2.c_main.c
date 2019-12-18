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
 int r_main_r2pipe (int,char**) ; 
 int r_main_radare2 (int,char**) ; 
 scalar_t__ strstr (char*,char*) ; 

int main(int argc, char **argv) {
	if (argc > 0 && strstr (argv[0], "r2p")) {
		return r_main_r2pipe (argc, argv);
	}
	return r_main_radare2 (argc, argv);
}