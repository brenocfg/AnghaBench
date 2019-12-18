#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wgl_dc_data {struct sw_framebuffer* sw_data; } ;
struct sw_framebuffer {TYPE_1__* gl_visual; } ;
struct sw_context {int /*<<< orphan*/  Mode; struct sw_framebuffer* fb; int /*<<< orphan*/  gl_ctx; } ;
struct TYPE_2__ {scalar_t__ DBflag; } ;
typedef  int /*<<< orphan*/ * DHGLRC ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct sw_context* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sw_context*) ; 
 int /*<<< orphan*/  gl_create_context (TYPE_1__*,int /*<<< orphan*/ *,struct sw_context*) ; 

DHGLRC sw_CreateContext(struct wgl_dc_data* dc_data)
{
    struct sw_context* sw_ctx;
    struct sw_framebuffer* fb = dc_data->sw_data;

    sw_ctx = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*sw_ctx));
    if(!sw_ctx)
        return NULL;
    
    /* Initialize the context */
    sw_ctx->gl_ctx = gl_create_context(fb->gl_visual, NULL, sw_ctx);
    if(!sw_ctx->gl_ctx)
    {
        ERR("Failed to initialize the mesa context.\n");
        HeapFree(GetProcessHeap(), 0, sw_ctx);
        return NULL;
    }
    
    sw_ctx->fb = fb;

    /* Choose relevant default */
    sw_ctx->Mode = fb->gl_visual->DBflag ? GL_BACK : GL_FRONT;

    return (DHGLRC)sw_ctx;
}