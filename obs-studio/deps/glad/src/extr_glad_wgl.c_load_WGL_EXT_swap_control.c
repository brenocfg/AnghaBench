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
typedef  scalar_t__ PFNWGLSWAPINTERVALEXTPROC ;
typedef  scalar_t__ PFNWGLGETSWAPINTERVALEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_EXT_swap_control ; 
 scalar_t__ glad_wglGetSwapIntervalEXT ; 
 scalar_t__ glad_wglSwapIntervalEXT ; 

__attribute__((used)) static void load_WGL_EXT_swap_control(GLADloadproc load) {
	if(!GLAD_WGL_EXT_swap_control) return;
	glad_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
	glad_wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)load("wglGetSwapIntervalEXT");
}