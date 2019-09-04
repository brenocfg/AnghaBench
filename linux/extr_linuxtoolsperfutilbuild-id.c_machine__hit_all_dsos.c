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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct machine {TYPE_1__ dsos; } ;

/* Variables and functions */
 int __dsos__hit_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int machine__hit_all_dsos(struct machine *machine)
{
	return __dsos__hit_all(&machine->dsos.head);
}