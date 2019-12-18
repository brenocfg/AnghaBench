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

void print_usage(void)
{
  fprintf(stderr, "usage: dgfirmware [<opts>] <img>\n");
  fprintf(stderr, "  <img>               firmware image filename\n");
  fprintf(stderr, "  <opts>  -h          print this message\n");
  fprintf(stderr, "          -f          fix the checksum\n");
  fprintf(stderr, "          -x  <file>  extract the rootfs file to <file>\n");
  fprintf(stderr, "          -xk <file>  extract the kernel to <file>\n");
  fprintf(stderr, "          -m  <file>  merge in rootfs fil\e from <file>\n");
  fprintf(stderr, "          -k  <file>  merge in kernel from <file>\n");
  fprintf(stderr, "          -w  <file>  write back the modified firmware\n");
}