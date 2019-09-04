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
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*) ; 

__attribute__((used)) static void print_device(const char *busid, const char *vendor,
			 const char *product, bool parsable)
{
	if (parsable)
		printf("busid=%s#usbid=%.4s:%.4s#", busid, vendor, product);
	else
		printf(" - busid %s (%.4s:%.4s)\n", busid, vendor, product);
}