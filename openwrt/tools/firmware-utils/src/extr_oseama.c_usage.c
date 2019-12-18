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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage() {
	printf("Usage:\n");
	printf("\n");
	printf("Info about Seama seal (container):\n");
	printf("\toseama info <file> [options]\n");
	printf("\t-e\t\t\t\tprint info about specified entity only\n");
	printf("\n");
	printf("Create Seama entity:\n");
	printf("\toseama entity <file> [options]\n");
	printf("\t-m meta\t\t\t\tmeta into to put in header\n");
	printf("\t-f file\t\t\t\tappend content from file\n");
	printf("\t-b offset\t\t\tappend zeros till reaching absolute offset\n");
	printf("\n");
	printf("Extract from Seama seal (container):\n");
	printf("\toseama extract <file> [options]\n");
	printf("\t-e\t\t\t\tindex of entity to extract\n");
	printf("\t-o file\t\t\t\toutput file\n");
}