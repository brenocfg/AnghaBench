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
typedef  scalar_t__ PFNWGLRELEASEPBUFFERDCEXTPROC ;
typedef  scalar_t__ PFNWGLQUERYPBUFFEREXTPROC ;
typedef  scalar_t__ PFNWGLGETPBUFFERDCEXTPROC ;
typedef  scalar_t__ PFNWGLDESTROYPBUFFEREXTPROC ;
typedef  scalar_t__ PFNWGLCREATEPBUFFEREXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_EXT_pbuffer ; 
 scalar_t__ glad_wglCreatePbufferEXT ; 
 scalar_t__ glad_wglDestroyPbufferEXT ; 
 scalar_t__ glad_wglGetPbufferDCEXT ; 
 scalar_t__ glad_wglQueryPbufferEXT ; 
 scalar_t__ glad_wglReleasePbufferDCEXT ; 

__attribute__((used)) static void load_WGL_EXT_pbuffer(GLADloadproc load) {
	if(!GLAD_WGL_EXT_pbuffer) return;
	glad_wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC)load("wglCreatePbufferEXT");
	glad_wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC)load("wglGetPbufferDCEXT");
	glad_wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC)load("wglReleasePbufferDCEXT");
	glad_wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC)load("wglDestroyPbufferEXT");
	glad_wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC)load("wglQueryPbufferEXT");
}