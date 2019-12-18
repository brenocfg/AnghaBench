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
typedef  scalar_t__ PFNGLTEXTURECOLORMASKSGISPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIS_texture_color_mask ; 
 scalar_t__ glad_glTextureColorMaskSGIS ; 

__attribute__((used)) static void load_GL_SGIS_texture_color_mask(GLADloadproc load) {
	if(!GLAD_GL_SGIS_texture_color_mask) return;
	glad_glTextureColorMaskSGIS = (PFNGLTEXTURECOLORMASKSGISPROC)load("glTextureColorMaskSGIS");
}