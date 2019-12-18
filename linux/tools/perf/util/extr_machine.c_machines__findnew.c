#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strlist {int dummy; } ;
struct machines {int dummy; } ;
struct machine {scalar_t__ pid; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {char* guestmount; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_GUEST_KERNEL_ID ; 
 scalar_t__ HOST_KERNEL_ID ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 struct machine* machines__add (struct machines*,scalar_t__,char const*) ; 
 struct machine* machines__find (struct machines*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlist__add (struct strlist*,char*) ; 
 int /*<<< orphan*/  strlist__has_entry (struct strlist*,char*) ; 
 struct strlist* strlist__new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ symbol_conf ; 

struct machine *machines__findnew(struct machines *machines, pid_t pid)
{
	char path[PATH_MAX];
	const char *root_dir = "";
	struct machine *machine = machines__find(machines, pid);

	if (machine && (machine->pid == pid))
		goto out;

	if ((pid != HOST_KERNEL_ID) &&
	    (pid != DEFAULT_GUEST_KERNEL_ID) &&
	    (symbol_conf.guestmount)) {
		sprintf(path, "%s/%d", symbol_conf.guestmount, pid);
		if (access(path, R_OK)) {
			static struct strlist *seen;

			if (!seen)
				seen = strlist__new(NULL, NULL);

			if (!strlist__has_entry(seen, path)) {
				pr_err("Can't access file %s\n", path);
				strlist__add(seen, path);
			}
			machine = NULL;
			goto out;
		}
		root_dir = path;
	}

	machine = machines__add(machines, pid, root_dir);
out:
	return machine;
}