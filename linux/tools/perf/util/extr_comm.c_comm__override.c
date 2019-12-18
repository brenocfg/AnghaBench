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
typedef  int /*<<< orphan*/  u64 ;
struct comm_str {int dummy; } ;
struct comm {int exec; int /*<<< orphan*/  start; struct comm_str* comm_str; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct comm_str* comm_str__findnew (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_str__put (struct comm_str*) ; 
 int /*<<< orphan*/  comm_str_root ; 

int comm__override(struct comm *comm, const char *str, u64 timestamp, bool exec)
{
	struct comm_str *new, *old = comm->comm_str;

	new = comm_str__findnew(str, &comm_str_root);
	if (!new)
		return -ENOMEM;

	comm_str__put(old);
	comm->comm_str = new;
	comm->start = timestamp;
	if (exec)
		comm->exec = true;

	return 0;
}