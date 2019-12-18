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
 unsigned long SIZE ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char*) ; 
 int test_strlen (char*) ; 

__attribute__((used)) static void test_one(char *s)
{
	unsigned long offset;

	for (offset = 0; offset < SIZE; offset++) {
		int x, y;
		unsigned long i;

		y = strlen(s + offset);
		x = test_strlen(s + offset);

		if (x != y) {
			printf("strlen() returned %d, should have returned %d (%p offset %ld)\n", x, y, s, offset);

			for (i = offset; i < SIZE; i++)
				printf("%02x ", s[i]);
			printf("\n");
		}
	}
}