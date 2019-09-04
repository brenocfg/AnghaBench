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
typedef  scalar_t__ PFNGLPIXELTEXGENPARAMETERIVSGISPROC ;
typedef  scalar_t__ PFNGLPIXELTEXGENPARAMETERISGISPROC ;
typedef  scalar_t__ PFNGLPIXELTEXGENPARAMETERFVSGISPROC ;
typedef  scalar_t__ PFNGLPIXELTEXGENPARAMETERFSGISPROC ;
typedef  scalar_t__ PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC ;
typedef  scalar_t__ PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIS_pixel_texture ; 
 scalar_t__ glad_glGetPixelTexGenParameterfvSGIS ; 
 scalar_t__ glad_glGetPixelTexGenParameterivSGIS ; 
 scalar_t__ glad_glPixelTexGenParameterfSGIS ; 
 scalar_t__ glad_glPixelTexGenParameterfvSGIS ; 
 scalar_t__ glad_glPixelTexGenParameteriSGIS ; 
 scalar_t__ glad_glPixelTexGenParameterivSGIS ; 

__attribute__((used)) static void load_GL_SGIS_pixel_texture(GLADloadproc load) {
	if(!GLAD_GL_SGIS_pixel_texture) return;
	glad_glPixelTexGenParameteriSGIS = (PFNGLPIXELTEXGENPARAMETERISGISPROC)load("glPixelTexGenParameteriSGIS");
	glad_glPixelTexGenParameterivSGIS = (PFNGLPIXELTEXGENPARAMETERIVSGISPROC)load("glPixelTexGenParameterivSGIS");
	glad_glPixelTexGenParameterfSGIS = (PFNGLPIXELTEXGENPARAMETERFSGISPROC)load("glPixelTexGenParameterfSGIS");
	glad_glPixelTexGenParameterfvSGIS = (PFNGLPIXELTEXGENPARAMETERFVSGISPROC)load("glPixelTexGenParameterfvSGIS");
	glad_glGetPixelTexGenParameterivSGIS = (PFNGLGETPIXELTEXGENPARAMETERIVSGISPROC)load("glGetPixelTexGenParameterivSGIS");
	glad_glGetPixelTexGenParameterfvSGIS = (PFNGLGETPIXELTEXGENPARAMETERFVSGISPROC)load("glGetPixelTexGenParameterfvSGIS");
}