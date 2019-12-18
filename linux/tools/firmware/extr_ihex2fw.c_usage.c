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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int usage(void)
{
	fprintf(stderr, "ihex2fw: Convert ihex files into binary "
		"representation for use by Linux kernel\n");
	fprintf(stderr, "usage: ihex2fw [<options>] <src.HEX> <dst.fw>\n");
	fprintf(stderr, "       -w: wide records (16-bit length)\n");
	fprintf(stderr, "       -s: sort records by address\n");
	fprintf(stderr, "       -j: include records for CS:IP/EIP address\n");
	return 1;
}