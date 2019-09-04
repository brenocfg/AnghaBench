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
typedef  scalar_t__ PFNWGLMAKECONTEXTCURRENTEXTPROC ;
typedef  scalar_t__ PFNWGLGETCURRENTREADDCEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_EXT_make_current_read ; 
 scalar_t__ glad_wglGetCurrentReadDCEXT ; 
 scalar_t__ glad_wglMakeContextCurrentEXT ; 

__attribute__((used)) static void load_WGL_EXT_make_current_read(GLADloadproc load) {
	if(!GLAD_WGL_EXT_make_current_read) return;
	glad_wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC)load("wglMakeContextCurrentEXT");
	glad_wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC)load("wglGetCurrentReadDCEXT");
}