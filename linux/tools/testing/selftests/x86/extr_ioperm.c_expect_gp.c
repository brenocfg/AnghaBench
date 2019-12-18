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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,unsigned short) ; 
 scalar_t__ try_outb (unsigned short) ; 

__attribute__((used)) static void expect_gp(unsigned short port)
{
	if (try_outb(port)) {
		printf("[FAIL]\toutb to 0x%02hx worked\n", port);
		exit(1);
	}

	printf("[OK]\toutb to 0x%02hx failed\n", port);
}