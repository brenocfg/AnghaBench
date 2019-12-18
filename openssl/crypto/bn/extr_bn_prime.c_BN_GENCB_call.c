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
struct TYPE_5__ {int (* cb_2 ) (int,int,TYPE_2__*) ;int /*<<< orphan*/  (* cb_1 ) (int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int ver; TYPE_1__ cb; int /*<<< orphan*/  arg; } ;
typedef  TYPE_2__ BN_GENCB ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ) ; 
 int stub2 (int,int,TYPE_2__*) ; 

int BN_GENCB_call(BN_GENCB *cb, int a, int b)
{
    /* No callback means continue */
    if (!cb)
        return 1;
    switch (cb->ver) {
    case 1:
        /* Deprecated-style callbacks */
        if (!cb->cb.cb_1)
            return 1;
        cb->cb.cb_1(a, b, cb->arg);
        return 1;
    case 2:
        /* New-style callbacks */
        return cb->cb.cb_2(a, b, cb);
    default:
        break;
    }
    /* Unrecognised callback type */
    return 0;
}