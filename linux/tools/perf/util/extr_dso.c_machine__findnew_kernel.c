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
struct machine {int dummy; } ;
struct dso {int kernel; } ;

/* Variables and functions */
 int /*<<< orphan*/  dso__set_short_name (struct dso*,char const*,int) ; 
 struct dso* machine__findnew_dso (struct machine*,char const*) ; 

struct dso *machine__findnew_kernel(struct machine *machine, const char *name,
				    const char *short_name, int dso_type)
{
	/*
	 * The kernel dso could be created by build_id processing.
	 */
	struct dso *dso = machine__findnew_dso(machine, name);

	/*
	 * We need to run this in all cases, since during the build_id
	 * processing we had no idea this was the kernel dso.
	 */
	if (dso != NULL) {
		dso__set_short_name(dso, short_name, false);
		dso->kernel = dso_type;
	}

	return dso;
}