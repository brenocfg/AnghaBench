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
 char* basename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 

void usage(char progname[], int exit_status)
{
	printf("Usage:\n");
	printf("1) %s -r [-s sleep]\n", basename(progname));
	printf("2) %s -b byte_offset\n", basename(progname));
	printf("3) %s -w byte_offset -v value\n\n", basename(progname));

	puts("\t-r [-s sleep]      : Dump EC registers");
	puts("\t                     If sleep is given, sleep x seconds,");
	puts("\t                     re-read EC registers and show changes");
	puts("\t-b offset          : Read value at byte_offset (in hex)");
	puts("\t-w offset -v value : Write value at byte_offset");
	puts("\t-h                 : Print this help\n\n");
	puts("Offsets and values are in hexadecimal number system.");
	puts("The offset and value must be between 0 and 0xff.");
	exit(exit_status);
}