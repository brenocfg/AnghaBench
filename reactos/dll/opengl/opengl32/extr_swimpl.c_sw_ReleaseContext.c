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
struct sw_context {int /*<<< orphan*/ * hook; } ;
typedef  scalar_t__ DHGLRC ;

/* Variables and functions */
 int /*<<< orphan*/  UnhookWindowsHookEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_make_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void sw_ReleaseContext(DHGLRC dhglrc)
{
    struct sw_context* sw_ctx = (struct sw_context*)dhglrc;
    
    /* Forward to mesa */
    gl_make_current(NULL, NULL);
    
    /* Unhook */
    if(sw_ctx->hook)
    {
        UnhookWindowsHookEx(sw_ctx->hook);
        sw_ctx->hook = NULL;
    }
}