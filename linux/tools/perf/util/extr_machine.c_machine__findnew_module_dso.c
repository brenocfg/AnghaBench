#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct machine {TYPE_1__ dsos; } ;
struct kmod_path {int /*<<< orphan*/  name; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 struct dso* __dsos__addnew (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct dso* __dsos__find (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso__get (struct dso*) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dso__set_module_info (struct dso*,struct kmod_path*,struct machine*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dso *machine__findnew_module_dso(struct machine *machine,
					       struct kmod_path *m,
					       const char *filename)
{
	struct dso *dso;

	down_write(&machine->dsos.lock);

	dso = __dsos__find(&machine->dsos, m->name, true);
	if (!dso) {
		dso = __dsos__addnew(&machine->dsos, m->name);
		if (dso == NULL)
			goto out_unlock;

		dso__set_module_info(dso, m, machine);
		dso__set_long_name(dso, strdup(filename), true);
	}

	dso__get(dso);
out_unlock:
	up_write(&machine->dsos.lock);
	return dso;
}