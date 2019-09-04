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
typedef  scalar_t__ PFNGLCOPYCOLORSUBTABLEEXTPROC ;
typedef  scalar_t__ PFNGLCOLORSUBTABLEEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_color_subtable ; 
 scalar_t__ glad_glColorSubTableEXT ; 
 scalar_t__ glad_glCopyColorSubTableEXT ; 

__attribute__((used)) static void load_GL_EXT_color_subtable(GLADloadproc load) {
	if(!GLAD_GL_EXT_color_subtable) return;
	glad_glColorSubTableEXT = (PFNGLCOLORSUBTABLEEXTPROC)load("glColorSubTableEXT");
	glad_glCopyColorSubTableEXT = (PFNGLCOPYCOLORSUBTABLEEXTPROC)load("glCopyColorSubTableEXT");
}