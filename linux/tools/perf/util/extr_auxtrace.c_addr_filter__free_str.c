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
struct addr_filter {int /*<<< orphan*/ * filename; int /*<<< orphan*/ * sym_to; int /*<<< orphan*/ * sym_from; int /*<<< orphan*/ * action; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void addr_filter__free_str(struct addr_filter *filt)
{
	zfree(&filt->str);
	filt->action   = NULL;
	filt->sym_from = NULL;
	filt->sym_to   = NULL;
	filt->filename = NULL;
}