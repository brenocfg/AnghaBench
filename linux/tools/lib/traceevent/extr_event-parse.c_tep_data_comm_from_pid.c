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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 char* find_cmdline (struct tep_handle*,int) ; 

const char *tep_data_comm_from_pid(struct tep_handle *tep, int pid)
{
	const char *comm;

	comm = find_cmdline(tep, pid);
	return comm;
}