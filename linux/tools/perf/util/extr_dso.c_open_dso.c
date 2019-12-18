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
struct nscookie {int dummy; } ;
struct machine {int dummy; } ;
struct dso {scalar_t__ binary_type; int /*<<< orphan*/  nsinfo; } ;

/* Variables and functions */
 scalar_t__ DSO_BINARY_TYPE__BUILD_ID_CACHE ; 
 int __open_dso (struct dso*,struct machine*) ; 
 int /*<<< orphan*/  check_data_close () ; 
 int /*<<< orphan*/  dso__list_add (struct dso*) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (int /*<<< orphan*/ ,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 

__attribute__((used)) static int open_dso(struct dso *dso, struct machine *machine)
{
	int fd;
	struct nscookie nsc;

	if (dso->binary_type != DSO_BINARY_TYPE__BUILD_ID_CACHE)
		nsinfo__mountns_enter(dso->nsinfo, &nsc);
	fd = __open_dso(dso, machine);
	if (dso->binary_type != DSO_BINARY_TYPE__BUILD_ID_CACHE)
		nsinfo__mountns_exit(&nsc);

	if (fd >= 0) {
		dso__list_add(dso);
		/*
		 * Check if we crossed the allowed number
		 * of opened DSOs and close one if needed.
		 */
		check_data_close();
	}

	return fd;
}