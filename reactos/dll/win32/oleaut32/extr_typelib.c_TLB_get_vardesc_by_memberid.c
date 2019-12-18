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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ memid; } ;
struct TYPE_6__ {TYPE_1__ vardesc; } ;
typedef  TYPE_2__ TLBVarDesc ;
typedef  scalar_t__ MEMBERID ;

/* Variables and functions */

__attribute__((used)) static inline TLBVarDesc *TLB_get_vardesc_by_memberid(TLBVarDesc *vardescs,
        UINT n, MEMBERID memid)
{
    while(n){
        if(vardescs->vardesc.memid == memid)
            return vardescs;
        ++vardescs;
        --n;
    }
    return NULL;
}