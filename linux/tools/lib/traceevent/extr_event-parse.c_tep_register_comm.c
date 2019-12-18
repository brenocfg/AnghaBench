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
 int _tep_register_comm (struct tep_handle*,char const*,int,int) ; 

int tep_register_comm(struct tep_handle *tep, const char *comm, int pid)
{
	return _tep_register_comm(tep, comm, pid, false);
}