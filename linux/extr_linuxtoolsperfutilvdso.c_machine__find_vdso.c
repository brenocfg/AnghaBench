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
struct thread {int dummy; } ;
struct machine {int /*<<< orphan*/  dsos; } ;
struct dso {int dummy; } ;
typedef  enum dso_type { ____Placeholder_dso_type } dso_type ;

/* Variables and functions */
 int /*<<< orphan*/  DSO__NAME_VDSO ; 
 int /*<<< orphan*/  DSO__NAME_VDSO32 ; 
 int /*<<< orphan*/  DSO__NAME_VDSOX32 ; 
#define  DSO__TYPE_32BIT 131 
#define  DSO__TYPE_64BIT 130 
#define  DSO__TYPE_UNKNOWN 129 
#define  DSO__TYPE_X32BIT 128 
 struct dso* __dsos__find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int dso__type (struct dso*,struct machine*) ; 
 int machine__thread_dso_type (struct machine*,struct thread*) ; 

__attribute__((used)) static struct dso *machine__find_vdso(struct machine *machine,
				      struct thread *thread)
{
	struct dso *dso = NULL;
	enum dso_type dso_type;

	dso_type = machine__thread_dso_type(machine, thread);
	switch (dso_type) {
	case DSO__TYPE_32BIT:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO32, true);
		if (!dso) {
			dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO,
					   true);
			if (dso && dso_type != dso__type(dso, machine))
				dso = NULL;
		}
		break;
	case DSO__TYPE_X32BIT:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSOX32, true);
		break;
	case DSO__TYPE_64BIT:
	case DSO__TYPE_UNKNOWN:
	default:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO, true);
		break;
	}

	return dso;
}