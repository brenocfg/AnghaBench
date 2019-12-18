#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int as_uintptr; } ;
struct TYPE_7__ {int tag; TYPE_1__ u; } ;
struct TYPE_8__ {double n; TYPE_2__ s; } ;
struct TYPE_9__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ jsval_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSV_NUMBER ; 

__attribute__((used)) static inline jsval_t jsval_number(double n)
{
    jsval_t ret;
#ifdef JSVAL_DOUBLE_LAYOUT_PTR32
    ret.u.n = n;
    /* normalize NaN value */
    if((ret.u.s.tag & 0x7ff00000) == 0x7ff00000) {
        /* isinf */
        if(ret.u.s.tag & 0xfffff) {
            ret.u.s.tag = 0x7ff00000;
            ret.u.s.u.as_uintptr = ~0;
        }else if(ret.u.s.u.as_uintptr) {
            ret.u.s.tag = 0x7ff00000;
        }
    }
#else
    ret.type = JSV_NUMBER;
    ret.u.n = n;
#endif
    return ret;
}