#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  VT_I4 128 
 int V_I4 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 

int convert_child_id(VARIANT *v)
{
    switch(V_VT(v)) {
    case VT_I4:
        return V_I4(v);
    default:
        FIXME("unhandled child ID variant type: %d\n", V_VT(v));
        return -1;
    }
}