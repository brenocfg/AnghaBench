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
typedef  scalar_t__ PFNGLTEXPARAMETERIUIVEXTPROC ;
typedef  scalar_t__ PFNGLTEXPARAMETERIIVEXTPROC ;
typedef  scalar_t__ PFNGLGETTEXPARAMETERIUIVEXTPROC ;
typedef  scalar_t__ PFNGLGETTEXPARAMETERIIVEXTPROC ;
typedef  scalar_t__ PFNGLCLEARCOLORIUIEXTPROC ;
typedef  scalar_t__ PFNGLCLEARCOLORIIEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_texture_integer ; 
 scalar_t__ glad_glClearColorIiEXT ; 
 scalar_t__ glad_glClearColorIuiEXT ; 
 scalar_t__ glad_glGetTexParameterIivEXT ; 
 scalar_t__ glad_glGetTexParameterIuivEXT ; 
 scalar_t__ glad_glTexParameterIivEXT ; 
 scalar_t__ glad_glTexParameterIuivEXT ; 

__attribute__((used)) static void load_GL_EXT_texture_integer(GLADloadproc load) {
	if(!GLAD_GL_EXT_texture_integer) return;
	glad_glTexParameterIivEXT = (PFNGLTEXPARAMETERIIVEXTPROC)load("glTexParameterIivEXT");
	glad_glTexParameterIuivEXT = (PFNGLTEXPARAMETERIUIVEXTPROC)load("glTexParameterIuivEXT");
	glad_glGetTexParameterIivEXT = (PFNGLGETTEXPARAMETERIIVEXTPROC)load("glGetTexParameterIivEXT");
	glad_glGetTexParameterIuivEXT = (PFNGLGETTEXPARAMETERIUIVEXTPROC)load("glGetTexParameterIuivEXT");
	glad_glClearColorIiEXT = (PFNGLCLEARCOLORIIEXTPROC)load("glClearColorIiEXT");
	glad_glClearColorIuiEXT = (PFNGLCLEARCOLORIUIEXTPROC)load("glClearColorIuiEXT");
}