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
struct mp_log {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* DebugMessageCallback ) (int /*<<< orphan*/ *,struct mp_log*) ;} ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/ * gl_debug_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct mp_log*) ; 

void gl_set_debug_logger(GL *gl, struct mp_log *log)
{
    if (gl->DebugMessageCallback)
        gl->DebugMessageCallback(log ? gl_debug_cb : NULL, log);
}