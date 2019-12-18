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
typedef  scalar_t__ PFNWGLSETPBUFFERATTRIBARBPROC ;
typedef  scalar_t__ PFNWGLRELEASETEXIMAGEARBPROC ;
typedef  scalar_t__ PFNWGLBINDTEXIMAGEARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_ARB_render_texture ; 
 scalar_t__ glad_wglBindTexImageARB ; 
 scalar_t__ glad_wglReleaseTexImageARB ; 
 scalar_t__ glad_wglSetPbufferAttribARB ; 

__attribute__((used)) static void load_WGL_ARB_render_texture(GLADloadproc load) {
	if(!GLAD_WGL_ARB_render_texture) return;
	glad_wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC)load("wglBindTexImageARB");
	glad_wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC)load("wglReleaseTexImageARB");
	glad_wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC)load("wglSetPbufferAttribARB");
}