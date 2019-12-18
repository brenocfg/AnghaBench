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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_addr (struct sockaddr*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
callback(struct sockaddr *addr, struct sockaddr *mask, void *unused)
{
	printf("addr: ");
	print_addr(addr);
	printf("  mask: ");
	print_addr(mask);
	printf("\n");
}