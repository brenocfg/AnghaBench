#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* language; struct TYPE_4__* type; struct TYPE_4__* data; struct TYPE_4__* timestr; struct TYPE_4__* name; } ;
typedef  TYPE_1__ r_pe_resource ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void _free_resource(r_pe_resource *rs) {
	if (rs) {
		free (rs->name);
		free (rs->timestr);
		free (rs->data);
		free (rs->type);
		free (rs->language);
		free (rs);
	}
}