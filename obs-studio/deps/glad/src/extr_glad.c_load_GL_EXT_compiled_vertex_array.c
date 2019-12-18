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
typedef  scalar_t__ PFNGLUNLOCKARRAYSEXTPROC ;
typedef  scalar_t__ PFNGLLOCKARRAYSEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_compiled_vertex_array ; 
 scalar_t__ glad_glLockArraysEXT ; 
 scalar_t__ glad_glUnlockArraysEXT ; 

__attribute__((used)) static void load_GL_EXT_compiled_vertex_array(GLADloadproc load) {
	if(!GLAD_GL_EXT_compiled_vertex_array) return;
	glad_glLockArraysEXT = (PFNGLLOCKARRAYSEXTPROC)load("glLockArraysEXT");
	glad_glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC)load("glUnlockArraysEXT");
}