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
typedef  scalar_t__ PFNGLTEXIMAGE3DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE2DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKIPROC ;
typedef  scalar_t__ PFNGLGETMULTISAMPLEFVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_texture_multisample ; 
 scalar_t__ glad_glGetMultisamplefv ; 
 scalar_t__ glad_glSampleMaski ; 
 scalar_t__ glad_glTexImage2DMultisample ; 
 scalar_t__ glad_glTexImage3DMultisample ; 

__attribute__((used)) static void load_GL_ARB_texture_multisample(GLADloadproc load) {
	if(!GLAD_GL_ARB_texture_multisample) return;
	glad_glTexImage2DMultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)load("glTexImage2DMultisample");
	glad_glTexImage3DMultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)load("glTexImage3DMultisample");
	glad_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)load("glGetMultisamplefv");
	glad_glSampleMaski = (PFNGLSAMPLEMASKIPROC)load("glSampleMaski");
}