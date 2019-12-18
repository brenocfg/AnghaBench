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
struct TYPE_3__ {void (* _enter ) () ;void (* _exit ) () ;} ;
struct TYPE_4__ {TYPE_1__ CRIS; } ;

/* Variables and functions */
 TYPE_2__ WIZCHIP ; 
 void wizchip_cris_enter () ; 
 void wizchip_cris_exit () ; 

void reg_wizchip_cris_cbfunc(void(*cris_en)(void), void(*cris_ex)(void))
{
   if(!cris_en || !cris_ex)
   {
      WIZCHIP.CRIS._enter = wizchip_cris_enter;
      WIZCHIP.CRIS._exit  = wizchip_cris_exit;
   }
   else
   {
      WIZCHIP.CRIS._enter = cris_en;
      WIZCHIP.CRIS._exit  = cris_ex;
   }
}