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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,int,int,int) ; 

__attribute__((used)) static void print_size(const char *label, uint32_t val)
{
	printf("%s cache size: %#10x %10dB %10dK\n", label, val, val, val / 1024);
}