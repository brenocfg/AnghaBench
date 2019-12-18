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
typedef  scalar_t__ PLpgSQL_label_type ;

/* Variables and functions */
 int /*<<< orphan*/  PLPGSQL_NSTYPE_LABEL ; 
 int /*<<< orphan*/  plpgsql_ns_additem (int /*<<< orphan*/ ,int,char const*) ; 

void
plpgsql_ns_push(const char *label, PLpgSQL_label_type label_type)
{
	if (label == NULL)
		label = "";
	plpgsql_ns_additem(PLPGSQL_NSTYPE_LABEL, (int) label_type, label);
}