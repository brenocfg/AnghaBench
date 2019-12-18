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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_MAX ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ is_placeholder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t browscap_compute_prefix_len(zend_string *pattern) {
	size_t i;
	for (i = 0; i < ZSTR_LEN(pattern); i++) {
		if (is_placeholder(ZSTR_VAL(pattern)[i])) {
			break;
		}
	}
	return (uint8_t)MIN(i, UINT8_MAX);
}