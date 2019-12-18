#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void (* cb_1 ) (int,int,void*) ;} ;
struct TYPE_5__ {int ver; TYPE_1__ cb; void* arg; } ;
typedef  TYPE_2__ BN_GENCB ;

/* Variables and functions */

void BN_GENCB_set_old(BN_GENCB *gencb, void (*callback) (int, int, void *),
                      void *cb_arg)
{
    BN_GENCB *tmp_gencb = gencb;
    tmp_gencb->ver = 1;
    tmp_gencb->arg = cb_arg;
    tmp_gencb->cb.cb_1 = callback;
}