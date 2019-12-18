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
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERIEXTPROC ;
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLPIXELTRANSFORMPARAMETERFEXTPROC ;
typedef  scalar_t__ PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_pixel_transform ; 
 scalar_t__ glad_glGetPixelTransformParameterfvEXT ; 
 scalar_t__ glad_glGetPixelTransformParameterivEXT ; 
 scalar_t__ glad_glPixelTransformParameterfEXT ; 
 scalar_t__ glad_glPixelTransformParameterfvEXT ; 
 scalar_t__ glad_glPixelTransformParameteriEXT ; 
 scalar_t__ glad_glPixelTransformParameterivEXT ; 

__attribute__((used)) static void load_GL_EXT_pixel_transform(GLADloadproc load) {
	if(!GLAD_GL_EXT_pixel_transform) return;
	glad_glPixelTransformParameteriEXT = (PFNGLPIXELTRANSFORMPARAMETERIEXTPROC)load("glPixelTransformParameteriEXT");
	glad_glPixelTransformParameterfEXT = (PFNGLPIXELTRANSFORMPARAMETERFEXTPROC)load("glPixelTransformParameterfEXT");
	glad_glPixelTransformParameterivEXT = (PFNGLPIXELTRANSFORMPARAMETERIVEXTPROC)load("glPixelTransformParameterivEXT");
	glad_glPixelTransformParameterfvEXT = (PFNGLPIXELTRANSFORMPARAMETERFVEXTPROC)load("glPixelTransformParameterfvEXT");
	glad_glGetPixelTransformParameterivEXT = (PFNGLGETPIXELTRANSFORMPARAMETERIVEXTPROC)load("glGetPixelTransformParameterivEXT");
	glad_glGetPixelTransformParameterfvEXT = (PFNGLGETPIXELTRANSFORMPARAMETERFVEXTPROC)load("glGetPixelTransformParameterfvEXT");
}