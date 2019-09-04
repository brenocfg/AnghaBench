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
struct TYPE_3__ {void (* _select ) () ;void (* _deselect ) () ;} ;
struct TYPE_4__ {TYPE_1__ CS; } ;

/* Variables and functions */
 TYPE_2__ WIZCHIP ; 
 void wizchip_cs_deselect () ; 
 void wizchip_cs_select () ; 

void reg_wizchip_cs_cbfunc(void(*cs_sel)(void), void(*cs_desel)(void))
{
   if(!cs_sel || !cs_desel)
   {
      WIZCHIP.CS._select   = wizchip_cs_select;
      WIZCHIP.CS._deselect = wizchip_cs_deselect;
   }
   else
   {
      WIZCHIP.CS._select   = cs_sel;
      WIZCHIP.CS._deselect = cs_desel;
   }
}