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
typedef  scalar_t__ ut32 ;

/* Variables and functions */

__attribute__((used)) static ut32 consume_chars(const char *input, char b) {
	ut32 i = 0;
	if (!input) {
		return i;
	}
	for (; *input == b; i++, input++) {
		/* nothing */
	}
	return i;
}