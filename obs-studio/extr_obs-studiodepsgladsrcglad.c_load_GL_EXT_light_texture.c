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
typedef  scalar_t__ PFNGLTEXTUREMATERIALEXTPROC ;
typedef  scalar_t__ PFNGLTEXTURELIGHTEXTPROC ;
typedef  scalar_t__ PFNGLAPPLYTEXTUREEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_light_texture ; 
 scalar_t__ glad_glApplyTextureEXT ; 
 scalar_t__ glad_glTextureLightEXT ; 
 scalar_t__ glad_glTextureMaterialEXT ; 

__attribute__((used)) static void load_GL_EXT_light_texture(GLADloadproc load) {
	if(!GLAD_GL_EXT_light_texture) return;
	glad_glApplyTextureEXT = (PFNGLAPPLYTEXTUREEXTPROC)load("glApplyTextureEXT");
	glad_glTextureLightEXT = (PFNGLTEXTURELIGHTEXTPROC)load("glTextureLightEXT");
	glad_glTextureMaterialEXT = (PFNGLTEXTUREMATERIALEXTPROC)load("glTextureMaterialEXT");
}