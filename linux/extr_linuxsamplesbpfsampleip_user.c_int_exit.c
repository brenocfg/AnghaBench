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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_fd ; 
 int /*<<< orphan*/  print_ip_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void int_exit(int sig)
{
	printf("\n");
	print_ip_map(map_fd[0]);
	exit(0);
}