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
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEEXTPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_paletted_texture ; 
 scalar_t__ glad_glColorTableEXT ; 
 scalar_t__ glad_glGetColorTableEXT ; 
 scalar_t__ glad_glGetColorTableParameterfvEXT ; 
 scalar_t__ glad_glGetColorTableParameterivEXT ; 

__attribute__((used)) static void load_GL_EXT_paletted_texture(GLADloadproc load) {
	if(!GLAD_GL_EXT_paletted_texture) return;
	glad_glColorTableEXT = (PFNGLCOLORTABLEEXTPROC)load("glColorTableEXT");
	glad_glGetColorTableEXT = (PFNGLGETCOLORTABLEEXTPROC)load("glGetColorTableEXT");
	glad_glGetColorTableParameterivEXT = (PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)load("glGetColorTableParameterivEXT");
	glad_glGetColorTableParameterfvEXT = (PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)load("glGetColorTableParameterfvEXT");
}