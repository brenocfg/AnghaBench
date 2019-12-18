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
typedef  scalar_t__ PFNGLPIXELTEXGENSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIX_pixel_texture ; 
 scalar_t__ glad_glPixelTexGenSGIX ; 

__attribute__((used)) static void load_GL_SGIX_pixel_texture(GLADloadproc load) {
	if(!GLAD_GL_SGIX_pixel_texture) return;
	glad_glPixelTexGenSGIX = (PFNGLPIXELTEXGENSGIXPROC)load("glPixelTexGenSGIX");
}