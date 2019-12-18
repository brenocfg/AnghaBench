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
typedef  scalar_t__ PFNGLUNIFORM4UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM4UIEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM3UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM3UIEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM2UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM2UIEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM1UIVEXTPROC ;
typedef  scalar_t__ PFNGLUNIFORM1UIEXTPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMUIVEXTPROC ;
typedef  scalar_t__ PFNGLGETFRAGDATALOCATIONEXTPROC ;
typedef  scalar_t__ PFNGLBINDFRAGDATALOCATIONEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_gpu_shader4 ; 
 scalar_t__ glad_glBindFragDataLocationEXT ; 
 scalar_t__ glad_glGetFragDataLocationEXT ; 
 scalar_t__ glad_glGetUniformuivEXT ; 
 scalar_t__ glad_glUniform1uiEXT ; 
 scalar_t__ glad_glUniform1uivEXT ; 
 scalar_t__ glad_glUniform2uiEXT ; 
 scalar_t__ glad_glUniform2uivEXT ; 
 scalar_t__ glad_glUniform3uiEXT ; 
 scalar_t__ glad_glUniform3uivEXT ; 
 scalar_t__ glad_glUniform4uiEXT ; 
 scalar_t__ glad_glUniform4uivEXT ; 

__attribute__((used)) static void load_GL_EXT_gpu_shader4(GLADloadproc load) {
	if(!GLAD_GL_EXT_gpu_shader4) return;
	glad_glGetUniformuivEXT = (PFNGLGETUNIFORMUIVEXTPROC)load("glGetUniformuivEXT");
	glad_glBindFragDataLocationEXT = (PFNGLBINDFRAGDATALOCATIONEXTPROC)load("glBindFragDataLocationEXT");
	glad_glGetFragDataLocationEXT = (PFNGLGETFRAGDATALOCATIONEXTPROC)load("glGetFragDataLocationEXT");
	glad_glUniform1uiEXT = (PFNGLUNIFORM1UIEXTPROC)load("glUniform1uiEXT");
	glad_glUniform2uiEXT = (PFNGLUNIFORM2UIEXTPROC)load("glUniform2uiEXT");
	glad_glUniform3uiEXT = (PFNGLUNIFORM3UIEXTPROC)load("glUniform3uiEXT");
	glad_glUniform4uiEXT = (PFNGLUNIFORM4UIEXTPROC)load("glUniform4uiEXT");
	glad_glUniform1uivEXT = (PFNGLUNIFORM1UIVEXTPROC)load("glUniform1uivEXT");
	glad_glUniform2uivEXT = (PFNGLUNIFORM2UIVEXTPROC)load("glUniform2uivEXT");
	glad_glUniform3uivEXT = (PFNGLUNIFORM3UIVEXTPROC)load("glUniform3uivEXT");
	glad_glUniform4uivEXT = (PFNGLUNIFORM4UIVEXTPROC)load("glUniform4uivEXT");
}