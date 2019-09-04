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
struct TYPE_4__ {int /*<<< orphan*/ * arg; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  cmdidx; } ;
typedef  TYPE_1__ exarg_T ;
typedef  int /*<<< orphan*/  ea ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_tabnew ; 
 int /*<<< orphan*/  ex_splitview (TYPE_1__*) ; 
 int /*<<< orphan*/  vim_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
tabpage_new()
{
    exarg_T	ea;

    vim_memset(&ea, 0, sizeof(ea));
    ea.cmdidx = CMD_tabnew;
    ea.cmd = (char_u *)"tabn";
    ea.arg = (char_u *)"";
    ex_splitview(&ea);
}