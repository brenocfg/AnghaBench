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
typedef  scalar_t__ PFNWGLSAVEBUFFERREGIONARBPROC ;
typedef  scalar_t__ PFNWGLRESTOREBUFFERREGIONARBPROC ;
typedef  scalar_t__ PFNWGLDELETEBUFFERREGIONARBPROC ;
typedef  scalar_t__ PFNWGLCREATEBUFFERREGIONARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_ARB_buffer_region ; 
 scalar_t__ glad_wglCreateBufferRegionARB ; 
 scalar_t__ glad_wglDeleteBufferRegionARB ; 
 scalar_t__ glad_wglRestoreBufferRegionARB ; 
 scalar_t__ glad_wglSaveBufferRegionARB ; 

__attribute__((used)) static void load_WGL_ARB_buffer_region(GLADloadproc load) {
	if(!GLAD_WGL_ARB_buffer_region) return;
	glad_wglCreateBufferRegionARB = (PFNWGLCREATEBUFFERREGIONARBPROC)load("wglCreateBufferRegionARB");
	glad_wglDeleteBufferRegionARB = (PFNWGLDELETEBUFFERREGIONARBPROC)load("wglDeleteBufferRegionARB");
	glad_wglSaveBufferRegionARB = (PFNWGLSAVEBUFFERREGIONARBPROC)load("wglSaveBufferRegionARB");
	glad_wglRestoreBufferRegionARB = (PFNWGLRESTOREBUFFERREGIONARBPROC)load("wglRestoreBufferRegionARB");
}