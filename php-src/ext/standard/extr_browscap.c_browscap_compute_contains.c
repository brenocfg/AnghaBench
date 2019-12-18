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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_MAX ; 
 size_t ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ is_placeholder (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t browscap_compute_contains(
		zend_string *pattern, size_t start_pos,
		uint16_t *contains_start, uint8_t *contains_len) {
	size_t i = start_pos;
	/* Find first non-placeholder character after prefix */
	for (; i < ZSTR_LEN(pattern); i++) {
		if (!is_placeholder(ZSTR_VAL(pattern)[i])) {
			/* Skip the case of a single non-placeholder character.
			 * Let's try to find something longer instead. */
			if (i + 1 < ZSTR_LEN(pattern) &&
					!is_placeholder(ZSTR_VAL(pattern)[i + 1])) {
				break;
			}
		}
	}
	*contains_start = (uint16_t)i;

	/* Find first placeholder character after that */
	for (; i < ZSTR_LEN(pattern); i++) {
		if (is_placeholder(ZSTR_VAL(pattern)[i])) {
			break;
		}
	}
	*contains_len = (uint8_t)MIN(i - *contains_start, UINT8_MAX);
	return i;
}