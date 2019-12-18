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
 unsigned int crc32 (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int main(int argc, char **argv) {
	unsigned int result;
	if (argc != 2) {
		printf("no string passed as argument\n");
		return -1;
	}
	result = crc32((unsigned char const *)argv[1], strlen(argv[1]));
	printf("0x%x\n", result);
	return 0;
}