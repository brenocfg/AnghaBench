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
typedef  scalar_t__ PFNGLTESTOBJECTAPPLEPROC ;
typedef  scalar_t__ PFNGLTESTFENCEAPPLEPROC ;
typedef  scalar_t__ PFNGLSETFENCEAPPLEPROC ;
typedef  scalar_t__ PFNGLISFENCEAPPLEPROC ;
typedef  scalar_t__ PFNGLGENFENCESAPPLEPROC ;
typedef  scalar_t__ PFNGLFINISHOBJECTAPPLEPROC ;
typedef  scalar_t__ PFNGLFINISHFENCEAPPLEPROC ;
typedef  scalar_t__ PFNGLDELETEFENCESAPPLEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_APPLE_fence ; 
 scalar_t__ glad_glDeleteFencesAPPLE ; 
 scalar_t__ glad_glFinishFenceAPPLE ; 
 scalar_t__ glad_glFinishObjectAPPLE ; 
 scalar_t__ glad_glGenFencesAPPLE ; 
 scalar_t__ glad_glIsFenceAPPLE ; 
 scalar_t__ glad_glSetFenceAPPLE ; 
 scalar_t__ glad_glTestFenceAPPLE ; 
 scalar_t__ glad_glTestObjectAPPLE ; 

__attribute__((used)) static void load_GL_APPLE_fence(GLADloadproc load) {
	if(!GLAD_GL_APPLE_fence) return;
	glad_glGenFencesAPPLE = (PFNGLGENFENCESAPPLEPROC)load("glGenFencesAPPLE");
	glad_glDeleteFencesAPPLE = (PFNGLDELETEFENCESAPPLEPROC)load("glDeleteFencesAPPLE");
	glad_glSetFenceAPPLE = (PFNGLSETFENCEAPPLEPROC)load("glSetFenceAPPLE");
	glad_glIsFenceAPPLE = (PFNGLISFENCEAPPLEPROC)load("glIsFenceAPPLE");
	glad_glTestFenceAPPLE = (PFNGLTESTFENCEAPPLEPROC)load("glTestFenceAPPLE");
	glad_glFinishFenceAPPLE = (PFNGLFINISHFENCEAPPLEPROC)load("glFinishFenceAPPLE");
	glad_glTestObjectAPPLE = (PFNGLTESTOBJECTAPPLEPROC)load("glTestObjectAPPLE");
	glad_glFinishObjectAPPLE = (PFNGLFINISHOBJECTAPPLEPROC)load("glFinishObjectAPPLE");
}