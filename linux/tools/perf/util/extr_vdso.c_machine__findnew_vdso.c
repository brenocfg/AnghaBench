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
struct vdso_info {int /*<<< orphan*/  vdso; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct machine {TYPE_1__ dsos; struct vdso_info* vdso_info; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO__NAME_VDSO ; 
 struct dso* __dsos__find (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct dso* __machine__addnew_vdso (struct machine*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ __machine__findnew_vdso_compat (struct machine*,struct thread*,struct vdso_info*,struct dso**) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso__get (struct dso*) ; 
 char* get_file (int /*<<< orphan*/ *) ; 
 struct dso* machine__find_vdso (struct machine*,struct thread*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct vdso_info* vdso_info__new () ; 

struct dso *machine__findnew_vdso(struct machine *machine,
				  struct thread *thread)
{
	struct vdso_info *vdso_info;
	struct dso *dso = NULL;

	down_write(&machine->dsos.lock);
	if (!machine->vdso_info)
		machine->vdso_info = vdso_info__new();

	vdso_info = machine->vdso_info;
	if (!vdso_info)
		goto out_unlock;

	dso = machine__find_vdso(machine, thread);
	if (dso)
		goto out_unlock;

#if BITS_PER_LONG == 64
	if (__machine__findnew_vdso_compat(machine, thread, vdso_info, &dso))
		goto out_unlock;
#endif

	dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO, true);
	if (!dso) {
		char *file;

		file = get_file(&vdso_info->vdso);
		if (file)
			dso = __machine__addnew_vdso(machine, DSO__NAME_VDSO, file);
	}

out_unlock:
	dso__get(dso);
	up_write(&machine->dsos.lock);
	return dso;
}