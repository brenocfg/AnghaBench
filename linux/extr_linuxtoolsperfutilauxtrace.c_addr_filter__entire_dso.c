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
struct symbol {scalar_t__ start; scalar_t__ end; } ;
struct dso {int dummy; } ;
struct addr_filter {scalar_t__ size; scalar_t__ addr; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int EINVAL ; 
 struct symbol* dso__first_symbol (struct dso*) ; 
 struct symbol* dso__last_symbol (struct dso*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int addr_filter__entire_dso(struct addr_filter *filt, struct dso *dso)
{
	struct symbol *first_sym = dso__first_symbol(dso);
	struct symbol *last_sym = dso__last_symbol(dso);

	if (!first_sym || !last_sym) {
		pr_err("Failed to determine filter for %s\nNo symbols found.\n",
		       filt->filename);
		return -EINVAL;
	}

	filt->addr = first_sym->start;
	filt->size = last_sym->end - first_sym->start;

	return 0;
}