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
 int /*<<< orphan*/  dump_blob (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* utilfdt_read (char*) ; 

int main(int argc, char *argv[])
{
	char *buf;

	if (argc < 2) {
		fprintf(stderr, "supply input filename\n");
		return 5;
	}

	buf = utilfdt_read(argv[1]);
	if (buf)
		dump_blob(buf);
	else
		return 10;

	return 0;
}