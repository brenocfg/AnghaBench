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
typedef  scalar_t__ PFNGLPROGRAMSTRINGARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETER4FVARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETER4FARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETER4DVARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETER4DARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETER4FVARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETER4FARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETER4DVARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETER4DARBPROC ;
typedef  scalar_t__ PFNGLISPROGRAMARBPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMSTRINGARBPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMIVARBPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMENVPARAMETERFVARBPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMENVPARAMETERDVARBPROC ;
typedef  scalar_t__ PFNGLGENPROGRAMSARBPROC ;
typedef  scalar_t__ PFNGLDELETEPROGRAMSARBPROC ;
typedef  scalar_t__ PFNGLBINDPROGRAMARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_fragment_program ; 
 scalar_t__ glad_glBindProgramARB ; 
 scalar_t__ glad_glDeleteProgramsARB ; 
 scalar_t__ glad_glGenProgramsARB ; 
 scalar_t__ glad_glGetProgramEnvParameterdvARB ; 
 scalar_t__ glad_glGetProgramEnvParameterfvARB ; 
 scalar_t__ glad_glGetProgramLocalParameterdvARB ; 
 scalar_t__ glad_glGetProgramLocalParameterfvARB ; 
 scalar_t__ glad_glGetProgramStringARB ; 
 scalar_t__ glad_glGetProgramivARB ; 
 scalar_t__ glad_glIsProgramARB ; 
 scalar_t__ glad_glProgramEnvParameter4dARB ; 
 scalar_t__ glad_glProgramEnvParameter4dvARB ; 
 scalar_t__ glad_glProgramEnvParameter4fARB ; 
 scalar_t__ glad_glProgramEnvParameter4fvARB ; 
 scalar_t__ glad_glProgramLocalParameter4dARB ; 
 scalar_t__ glad_glProgramLocalParameter4dvARB ; 
 scalar_t__ glad_glProgramLocalParameter4fARB ; 
 scalar_t__ glad_glProgramLocalParameter4fvARB ; 
 scalar_t__ glad_glProgramStringARB ; 

__attribute__((used)) static void load_GL_ARB_fragment_program(GLADloadproc load) {
	if(!GLAD_GL_ARB_fragment_program) return;
	glad_glProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC)load("glProgramStringARB");
	glad_glBindProgramARB = (PFNGLBINDPROGRAMARBPROC)load("glBindProgramARB");
	glad_glDeleteProgramsARB = (PFNGLDELETEPROGRAMSARBPROC)load("glDeleteProgramsARB");
	glad_glGenProgramsARB = (PFNGLGENPROGRAMSARBPROC)load("glGenProgramsARB");
	glad_glProgramEnvParameter4dARB = (PFNGLPROGRAMENVPARAMETER4DARBPROC)load("glProgramEnvParameter4dARB");
	glad_glProgramEnvParameter4dvARB = (PFNGLPROGRAMENVPARAMETER4DVARBPROC)load("glProgramEnvParameter4dvARB");
	glad_glProgramEnvParameter4fARB = (PFNGLPROGRAMENVPARAMETER4FARBPROC)load("glProgramEnvParameter4fARB");
	glad_glProgramEnvParameter4fvARB = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)load("glProgramEnvParameter4fvARB");
	glad_glProgramLocalParameter4dARB = (PFNGLPROGRAMLOCALPARAMETER4DARBPROC)load("glProgramLocalParameter4dARB");
	glad_glProgramLocalParameter4dvARB = (PFNGLPROGRAMLOCALPARAMETER4DVARBPROC)load("glProgramLocalParameter4dvARB");
	glad_glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)load("glProgramLocalParameter4fARB");
	glad_glProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)load("glProgramLocalParameter4fvARB");
	glad_glGetProgramEnvParameterdvARB = (PFNGLGETPROGRAMENVPARAMETERDVARBPROC)load("glGetProgramEnvParameterdvARB");
	glad_glGetProgramEnvParameterfvARB = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)load("glGetProgramEnvParameterfvARB");
	glad_glGetProgramLocalParameterdvARB = (PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC)load("glGetProgramLocalParameterdvARB");
	glad_glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)load("glGetProgramLocalParameterfvARB");
	glad_glGetProgramivARB = (PFNGLGETPROGRAMIVARBPROC)load("glGetProgramivARB");
	glad_glGetProgramStringARB = (PFNGLGETPROGRAMSTRINGARBPROC)load("glGetProgramStringARB");
	glad_glIsProgramARB = (PFNGLISPROGRAMARBPROC)load("glIsProgramARB");
}