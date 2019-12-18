#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_3__ {int /*<<< orphan*/  ret; } ;
typedef  TYPE_1__ call_frame_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsval_undefined () ; 

__attribute__((used)) static inline jsval_t steal_ret(call_frame_t *frame)
{
    jsval_t r = frame->ret;
    frame->ret = jsval_undefined();
    return r;
}