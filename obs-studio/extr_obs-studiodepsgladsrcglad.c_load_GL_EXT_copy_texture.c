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
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE3DEXTPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE2DEXTPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE1DEXTPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE2DEXTPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE1DEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_copy_texture ; 
 scalar_t__ glad_glCopyTexImage1DEXT ; 
 scalar_t__ glad_glCopyTexImage2DEXT ; 
 scalar_t__ glad_glCopyTexSubImage1DEXT ; 
 scalar_t__ glad_glCopyTexSubImage2DEXT ; 
 scalar_t__ glad_glCopyTexSubImage3DEXT ; 

__attribute__((used)) static void load_GL_EXT_copy_texture(GLADloadproc load) {
	if(!GLAD_GL_EXT_copy_texture) return;
	glad_glCopyTexImage1DEXT = (PFNGLCOPYTEXIMAGE1DEXTPROC)load("glCopyTexImage1DEXT");
	glad_glCopyTexImage2DEXT = (PFNGLCOPYTEXIMAGE2DEXTPROC)load("glCopyTexImage2DEXT");
	glad_glCopyTexSubImage1DEXT = (PFNGLCOPYTEXSUBIMAGE1DEXTPROC)load("glCopyTexSubImage1DEXT");
	glad_glCopyTexSubImage2DEXT = (PFNGLCOPYTEXSUBIMAGE2DEXTPROC)load("glCopyTexSubImage2DEXT");
	glad_glCopyTexSubImage3DEXT = (PFNGLCOPYTEXSUBIMAGE3DEXTPROC)load("glCopyTexSubImage3DEXT");
}