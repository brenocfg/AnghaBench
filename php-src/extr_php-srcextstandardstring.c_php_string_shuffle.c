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
typedef  int zend_long ;

/* Variables and functions */
 int php_mt_rand_range (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void php_string_shuffle(char *str, zend_long len) /* {{{ */
{
	zend_long n_elems, rnd_idx, n_left;
	char temp;
	/* The implementation is stolen from array_data_shuffle       */
	/* Thus the characteristics of the randomization are the same */
	n_elems = len;

	if (n_elems <= 1) {
		return;
	}

	n_left = n_elems;

	while (--n_left) {
		rnd_idx = php_mt_rand_range(0, n_left);
		if (rnd_idx != n_left) {
			temp = str[n_left];
			str[n_left] = str[rnd_idx];
			str[rnd_idx] = temp;
		}
	}
}