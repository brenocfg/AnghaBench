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
struct vc_data {TYPE_1__* vc_sw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_switch ) (struct vc_data*) ;int /*<<< orphan*/  (* con_flush_scrollback ) (struct vc_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  set_origin (struct vc_data*) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*) ; 
 int /*<<< orphan*/  stub2 (struct vc_data*) ; 

__attribute__((used)) static void flush_scrollback(struct vc_data *vc)
{
	WARN_CONSOLE_UNLOCKED();

	set_origin(vc);
	if (vc->vc_sw->con_flush_scrollback)
		vc->vc_sw->con_flush_scrollback(vc);
	else
		vc->vc_sw->con_switch(vc);
}