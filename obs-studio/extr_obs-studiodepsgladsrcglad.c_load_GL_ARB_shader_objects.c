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
typedef  scalar_t__ PFNGLVALIDATEPROGRAMARBPROC ;
typedef  scalar_t__ PFNGLUSEPROGRAMOBJECTARBPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM4IVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM4IARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM4FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM4FARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM3IVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM3IARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM3FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM3FARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM2IVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM2IARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM2FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM2FARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1IVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1IARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1FVARBPROC ;
typedef  scalar_t__ PFNGLUNIFORM1FARBPROC ;
typedef  scalar_t__ PFNGLSHADERSOURCEARBPROC ;
typedef  scalar_t__ PFNGLLINKPROGRAMARBPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMLOCATIONARBPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMIVARBPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMFVARBPROC ;
typedef  scalar_t__ PFNGLGETSHADERSOURCEARBPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPARAMETERIVARBPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPARAMETERFVARBPROC ;
typedef  scalar_t__ PFNGLGETINFOLOGARBPROC ;
typedef  scalar_t__ PFNGLGETHANDLEARBPROC ;
typedef  scalar_t__ PFNGLGETATTACHEDOBJECTSARBPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMARBPROC ;
typedef  scalar_t__ PFNGLDETACHOBJECTARBPROC ;
typedef  scalar_t__ PFNGLDELETEOBJECTARBPROC ;
typedef  scalar_t__ PFNGLCREATESHADEROBJECTARBPROC ;
typedef  scalar_t__ PFNGLCREATEPROGRAMOBJECTARBPROC ;
typedef  scalar_t__ PFNGLCOMPILESHADERARBPROC ;
typedef  scalar_t__ PFNGLATTACHOBJECTARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_shader_objects ; 
 scalar_t__ glad_glAttachObjectARB ; 
 scalar_t__ glad_glCompileShaderARB ; 
 scalar_t__ glad_glCreateProgramObjectARB ; 
 scalar_t__ glad_glCreateShaderObjectARB ; 
 scalar_t__ glad_glDeleteObjectARB ; 
 scalar_t__ glad_glDetachObjectARB ; 
 scalar_t__ glad_glGetActiveUniformARB ; 
 scalar_t__ glad_glGetAttachedObjectsARB ; 
 scalar_t__ glad_glGetHandleARB ; 
 scalar_t__ glad_glGetInfoLogARB ; 
 scalar_t__ glad_glGetObjectParameterfvARB ; 
 scalar_t__ glad_glGetObjectParameterivARB ; 
 scalar_t__ glad_glGetShaderSourceARB ; 
 scalar_t__ glad_glGetUniformLocationARB ; 
 scalar_t__ glad_glGetUniformfvARB ; 
 scalar_t__ glad_glGetUniformivARB ; 
 scalar_t__ glad_glLinkProgramARB ; 
 scalar_t__ glad_glShaderSourceARB ; 
 scalar_t__ glad_glUniform1fARB ; 
 scalar_t__ glad_glUniform1fvARB ; 
 scalar_t__ glad_glUniform1iARB ; 
 scalar_t__ glad_glUniform1ivARB ; 
 scalar_t__ glad_glUniform2fARB ; 
 scalar_t__ glad_glUniform2fvARB ; 
 scalar_t__ glad_glUniform2iARB ; 
 scalar_t__ glad_glUniform2ivARB ; 
 scalar_t__ glad_glUniform3fARB ; 
 scalar_t__ glad_glUniform3fvARB ; 
 scalar_t__ glad_glUniform3iARB ; 
 scalar_t__ glad_glUniform3ivARB ; 
 scalar_t__ glad_glUniform4fARB ; 
 scalar_t__ glad_glUniform4fvARB ; 
 scalar_t__ glad_glUniform4iARB ; 
 scalar_t__ glad_glUniform4ivARB ; 
 scalar_t__ glad_glUniformMatrix2fvARB ; 
 scalar_t__ glad_glUniformMatrix3fvARB ; 
 scalar_t__ glad_glUniformMatrix4fvARB ; 
 scalar_t__ glad_glUseProgramObjectARB ; 
 scalar_t__ glad_glValidateProgramARB ; 

__attribute__((used)) static void load_GL_ARB_shader_objects(GLADloadproc load) {
	if(!GLAD_GL_ARB_shader_objects) return;
	glad_glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)load("glDeleteObjectARB");
	glad_glGetHandleARB = (PFNGLGETHANDLEARBPROC)load("glGetHandleARB");
	glad_glDetachObjectARB = (PFNGLDETACHOBJECTARBPROC)load("glDetachObjectARB");
	glad_glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)load("glCreateShaderObjectARB");
	glad_glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)load("glShaderSourceARB");
	glad_glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)load("glCompileShaderARB");
	glad_glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)load("glCreateProgramObjectARB");
	glad_glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)load("glAttachObjectARB");
	glad_glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)load("glLinkProgramARB");
	glad_glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)load("glUseProgramObjectARB");
	glad_glValidateProgramARB = (PFNGLVALIDATEPROGRAMARBPROC)load("glValidateProgramARB");
	glad_glUniform1fARB = (PFNGLUNIFORM1FARBPROC)load("glUniform1fARB");
	glad_glUniform2fARB = (PFNGLUNIFORM2FARBPROC)load("glUniform2fARB");
	glad_glUniform3fARB = (PFNGLUNIFORM3FARBPROC)load("glUniform3fARB");
	glad_glUniform4fARB = (PFNGLUNIFORM4FARBPROC)load("glUniform4fARB");
	glad_glUniform1iARB = (PFNGLUNIFORM1IARBPROC)load("glUniform1iARB");
	glad_glUniform2iARB = (PFNGLUNIFORM2IARBPROC)load("glUniform2iARB");
	glad_glUniform3iARB = (PFNGLUNIFORM3IARBPROC)load("glUniform3iARB");
	glad_glUniform4iARB = (PFNGLUNIFORM4IARBPROC)load("glUniform4iARB");
	glad_glUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)load("glUniform1fvARB");
	glad_glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC)load("glUniform2fvARB");
	glad_glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC)load("glUniform3fvARB");
	glad_glUniform4fvARB = (PFNGLUNIFORM4FVARBPROC)load("glUniform4fvARB");
	glad_glUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)load("glUniform1ivARB");
	glad_glUniform2ivARB = (PFNGLUNIFORM2IVARBPROC)load("glUniform2ivARB");
	glad_glUniform3ivARB = (PFNGLUNIFORM3IVARBPROC)load("glUniform3ivARB");
	glad_glUniform4ivARB = (PFNGLUNIFORM4IVARBPROC)load("glUniform4ivARB");
	glad_glUniformMatrix2fvARB = (PFNGLUNIFORMMATRIX2FVARBPROC)load("glUniformMatrix2fvARB");
	glad_glUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)load("glUniformMatrix3fvARB");
	glad_glUniformMatrix4fvARB = (PFNGLUNIFORMMATRIX4FVARBPROC)load("glUniformMatrix4fvARB");
	glad_glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC)load("glGetObjectParameterfvARB");
	glad_glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)load("glGetObjectParameterivARB");
	glad_glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)load("glGetInfoLogARB");
	glad_glGetAttachedObjectsARB = (PFNGLGETATTACHEDOBJECTSARBPROC)load("glGetAttachedObjectsARB");
	glad_glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)load("glGetUniformLocationARB");
	glad_glGetActiveUniformARB = (PFNGLGETACTIVEUNIFORMARBPROC)load("glGetActiveUniformARB");
	glad_glGetUniformfvARB = (PFNGLGETUNIFORMFVARBPROC)load("glGetUniformfvARB");
	glad_glGetUniformivARB = (PFNGLGETUNIFORMIVARBPROC)load("glGetUniformivARB");
	glad_glGetShaderSourceARB = (PFNGLGETSHADERSOURCEARBPROC)load("glGetShaderSourceARB");
}