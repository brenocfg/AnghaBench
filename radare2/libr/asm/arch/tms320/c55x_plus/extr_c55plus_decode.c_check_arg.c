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

__attribute__((used)) static bool check_arg(ut32 ins_bits, int *err_code) {
	bool res = false;

	if ((ins_bits <= 31) | (ins_bits >= 128 && ins_bits < 160)) {
		res = true;
	} else if (ins_bits >= 32 && ins_bits <= 252) {
		res = false;
	} else {
		fprintf(stderr, "Invalid arg: %u\n", ins_bits);
		*err_code = -1;
	}

	return res;
}