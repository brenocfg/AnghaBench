#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* bin; } ;
struct TYPE_8__ {TYPE_2__* cur; } ;
struct TYPE_7__ {TYPE_1__* o; } ;
struct TYPE_6__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int r_list_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_unknown_file(RCore *core) {
	if (core->bin->cur && core->bin->cur->o) {
		return (r_list_empty (core->bin->cur->o->sections));
	}
	return true;
}