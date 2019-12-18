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
typedef  int ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 

char *get_tc2_tc1(ut32 ins_bits) {
	char *res = "tc1";
	if (ins_bits) {
		if (ins_bits != 1) {
			fprintf(stderr, "Invalid instruction TC2 or TC1 (%d)\n", ins_bits);
			return NULL;
		}
		res = "tc2";
	}
	return strdup (res);
}