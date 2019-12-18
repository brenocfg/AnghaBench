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
struct machine {int /*<<< orphan*/  dsos; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dsos__add (int /*<<< orphan*/ *,struct dso*) ; 
 struct dso* dso__new (char const*) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,char const*,int) ; 

__attribute__((used)) static struct dso *__machine__addnew_vdso(struct machine *machine, const char *short_name,
					  const char *long_name)
{
	struct dso *dso;

	dso = dso__new(short_name);
	if (dso != NULL) {
		__dsos__add(&machine->dsos, dso);
		dso__set_long_name(dso, long_name, false);
	}

	return dso;
}