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
struct comm {int exec; int /*<<< orphan*/  comm_str; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_str__findnew (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_str_root ; 
 int /*<<< orphan*/  free (struct comm*) ; 
 struct comm* zalloc (int) ; 

struct comm *comm__new(const char *str, u64 timestamp, bool exec)
{
	struct comm *comm = zalloc(sizeof(*comm));

	if (!comm)
		return NULL;

	comm->start = timestamp;
	comm->exec = exec;

	comm->comm_str = comm_str__findnew(str, &comm_str_root);
	if (!comm->comm_str) {
		free(comm);
		return NULL;
	}

	return comm;
}