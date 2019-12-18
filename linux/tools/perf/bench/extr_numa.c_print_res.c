#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  show_quiet; } ;
struct TYPE_4__ {TYPE_1__ p; } ;

/* Variables and functions */
 TYPE_2__* g ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_res(const char *name, double val,
		      const char *txt_unit, const char *txt_short, const char *txt_long)
{
	if (!name)
		name = "main,";

	if (!g->p.show_quiet)
		printf(" %-30s %15.3f, %-15s %s\n", name, val, txt_unit, txt_short);
	else
		printf(" %14.3f %s\n", val, txt_long);
}