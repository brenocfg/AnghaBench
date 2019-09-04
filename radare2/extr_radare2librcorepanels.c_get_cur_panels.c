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
struct TYPE_4__ {int /*<<< orphan*/  cur_panels; } ;
typedef  TYPE_1__ RPanelsRoot ;
typedef  int /*<<< orphan*/  RPanels ;

/* Variables and functions */
 int /*<<< orphan*/ * get_panels (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPanels *get_cur_panels(RPanelsRoot *panels_root) {
	return get_panels (panels_root, panels_root->cur_panels);
}