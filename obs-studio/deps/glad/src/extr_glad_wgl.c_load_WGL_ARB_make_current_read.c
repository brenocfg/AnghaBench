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
typedef  scalar_t__ PFNWGLMAKECONTEXTCURRENTARBPROC ;
typedef  scalar_t__ PFNWGLGETCURRENTREADDCARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_ARB_make_current_read ; 
 scalar_t__ glad_wglGetCurrentReadDCARB ; 
 scalar_t__ glad_wglMakeContextCurrentARB ; 

__attribute__((used)) static void load_WGL_ARB_make_current_read(GLADloadproc load) {
	if(!GLAD_WGL_ARB_make_current_read) return;
	glad_wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC)load("wglMakeContextCurrentARB");
	glad_wglGetCurrentReadDCARB = (PFNWGLGETCURRENTREADDCARBPROC)load("wglGetCurrentReadDCARB");
}