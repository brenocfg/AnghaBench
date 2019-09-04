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
typedef  scalar_t__ PFNGLUNMAPTEXTURE2DINTELPROC ;
typedef  scalar_t__ PFNGLSYNCTEXTUREINTELPROC ;
typedef  scalar_t__ PFNGLMAPTEXTURE2DINTELPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_INTEL_map_texture ; 
 scalar_t__ glad_glMapTexture2DINTEL ; 
 scalar_t__ glad_glSyncTextureINTEL ; 
 scalar_t__ glad_glUnmapTexture2DINTEL ; 

__attribute__((used)) static void load_GL_INTEL_map_texture(GLADloadproc load) {
	if(!GLAD_GL_INTEL_map_texture) return;
	glad_glSyncTextureINTEL = (PFNGLSYNCTEXTUREINTELPROC)load("glSyncTextureINTEL");
	glad_glUnmapTexture2DINTEL = (PFNGLUNMAPTEXTURE2DINTELPROC)load("glUnmapTexture2DINTEL");
	glad_glMapTexture2DINTEL = (PFNGLMAPTEXTURE2DINTELPROC)load("glMapTexture2DINTEL");
}