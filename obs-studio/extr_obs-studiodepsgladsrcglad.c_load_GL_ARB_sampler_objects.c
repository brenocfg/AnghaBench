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
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIUIVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERIIVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLSAMPLERPARAMETERFPROC ;
typedef  scalar_t__ PFNGLISSAMPLERPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERIUIVPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERIIVPROC ;
typedef  scalar_t__ PFNGLGETSAMPLERPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLGENSAMPLERSPROC ;
typedef  scalar_t__ PFNGLDELETESAMPLERSPROC ;
typedef  scalar_t__ PFNGLBINDSAMPLERPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_sampler_objects ; 
 scalar_t__ glad_glBindSampler ; 
 scalar_t__ glad_glDeleteSamplers ; 
 scalar_t__ glad_glGenSamplers ; 
 scalar_t__ glad_glGetSamplerParameterIiv ; 
 scalar_t__ glad_glGetSamplerParameterIuiv ; 
 scalar_t__ glad_glGetSamplerParameterfv ; 
 scalar_t__ glad_glGetSamplerParameteriv ; 
 scalar_t__ glad_glIsSampler ; 
 scalar_t__ glad_glSamplerParameterIiv ; 
 scalar_t__ glad_glSamplerParameterIuiv ; 
 scalar_t__ glad_glSamplerParameterf ; 
 scalar_t__ glad_glSamplerParameterfv ; 
 scalar_t__ glad_glSamplerParameteri ; 
 scalar_t__ glad_glSamplerParameteriv ; 

__attribute__((used)) static void load_GL_ARB_sampler_objects(GLADloadproc load) {
	if(!GLAD_GL_ARB_sampler_objects) return;
	glad_glGenSamplers = (PFNGLGENSAMPLERSPROC)load("glGenSamplers");
	glad_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC)load("glDeleteSamplers");
	glad_glIsSampler = (PFNGLISSAMPLERPROC)load("glIsSampler");
	glad_glBindSampler = (PFNGLBINDSAMPLERPROC)load("glBindSampler");
	glad_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC)load("glSamplerParameteri");
	glad_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC)load("glSamplerParameteriv");
	glad_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC)load("glSamplerParameterf");
	glad_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC)load("glSamplerParameterfv");
	glad_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC)load("glSamplerParameterIiv");
	glad_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)load("glSamplerParameterIuiv");
	glad_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)load("glGetSamplerParameteriv");
	glad_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)load("glGetSamplerParameterIiv");
	glad_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)load("glGetSamplerParameterfv");
	glad_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)load("glGetSamplerParameterIuiv");
}