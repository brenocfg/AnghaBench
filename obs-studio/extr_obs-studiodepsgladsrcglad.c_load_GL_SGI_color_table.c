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
typedef  scalar_t__ PFNGLGETCOLORTABLESGIPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERIVSGIPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERFVSGIPROC ;
typedef  scalar_t__ PFNGLCOPYCOLORTABLESGIPROC ;
typedef  scalar_t__ PFNGLCOLORTABLESGIPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPARAMETERIVSGIPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPARAMETERFVSGIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGI_color_table ; 
 scalar_t__ glad_glColorTableParameterfvSGI ; 
 scalar_t__ glad_glColorTableParameterivSGI ; 
 scalar_t__ glad_glColorTableSGI ; 
 scalar_t__ glad_glCopyColorTableSGI ; 
 scalar_t__ glad_glGetColorTableParameterfvSGI ; 
 scalar_t__ glad_glGetColorTableParameterivSGI ; 
 scalar_t__ glad_glGetColorTableSGI ; 

__attribute__((used)) static void load_GL_SGI_color_table(GLADloadproc load) {
	if(!GLAD_GL_SGI_color_table) return;
	glad_glColorTableSGI = (PFNGLCOLORTABLESGIPROC)load("glColorTableSGI");
	glad_glColorTableParameterfvSGI = (PFNGLCOLORTABLEPARAMETERFVSGIPROC)load("glColorTableParameterfvSGI");
	glad_glColorTableParameterivSGI = (PFNGLCOLORTABLEPARAMETERIVSGIPROC)load("glColorTableParameterivSGI");
	glad_glCopyColorTableSGI = (PFNGLCOPYCOLORTABLESGIPROC)load("glCopyColorTableSGI");
	glad_glGetColorTableSGI = (PFNGLGETCOLORTABLESGIPROC)load("glGetColorTableSGI");
	glad_glGetColorTableParameterfvSGI = (PFNGLGETCOLORTABLEPARAMETERFVSGIPROC)load("glGetColorTableParameterfvSGI");
	glad_glGetColorTableParameterivSGI = (PFNGLGETCOLORTABLEPARAMETERIVSGIPROC)load("glGetColorTableParameterivSGI");
}