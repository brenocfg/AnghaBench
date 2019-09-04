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
struct restart_block {int dummy; } ;

/* Variables and functions */
 long EINTR ; 

long do_no_restart_syscall(struct restart_block *param)
{
	return -EINTR;
}