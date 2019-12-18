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
struct TYPE_5__ {scalar_t__* text; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ subst; } ;
typedef  TYPE_2__ pp_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ def_define ; 
 int /*<<< orphan*/  push_buffer (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yy_scan_string (scalar_t__*) ; 

__attribute__((used)) static void expand_define(pp_entry_t *ppp)
{
	assert(ppp->type == def_define);

	if(ppp->subst.text && ppp->subst.text[0])
	{
		push_buffer(ppp, NULL, NULL, 0);
		yy_scan_string(ppp->subst.text);
	}
}