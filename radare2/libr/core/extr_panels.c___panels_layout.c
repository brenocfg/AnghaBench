#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* can; } ;
struct TYPE_5__ {scalar_t__ sy; scalar_t__ sx; } ;
typedef  TYPE_2__ RPanels ;

/* Variables and functions */
 int /*<<< orphan*/  __layout_default (TYPE_2__*) ; 

void __panels_layout (RPanels *panels) {
	panels->can->sx = 0;
	panels->can->sy = 0;
	__layout_default (panels);
}