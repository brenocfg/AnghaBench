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
typedef  scalar_t__ PFNGLPRIORITIZETEXTURESEXTPROC ;
typedef  scalar_t__ PFNGLISTEXTUREEXTPROC ;
typedef  scalar_t__ PFNGLGENTEXTURESEXTPROC ;
typedef  scalar_t__ PFNGLDELETETEXTURESEXTPROC ;
typedef  scalar_t__ PFNGLBINDTEXTUREEXTPROC ;
typedef  scalar_t__ PFNGLARETEXTURESRESIDENTEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_texture_object ; 
 scalar_t__ glad_glAreTexturesResidentEXT ; 
 scalar_t__ glad_glBindTextureEXT ; 
 scalar_t__ glad_glDeleteTexturesEXT ; 
 scalar_t__ glad_glGenTexturesEXT ; 
 scalar_t__ glad_glIsTextureEXT ; 
 scalar_t__ glad_glPrioritizeTexturesEXT ; 

__attribute__((used)) static void load_GL_EXT_texture_object(GLADloadproc load) {
	if(!GLAD_GL_EXT_texture_object) return;
	glad_glAreTexturesResidentEXT = (PFNGLARETEXTURESRESIDENTEXTPROC)load("glAreTexturesResidentEXT");
	glad_glBindTextureEXT = (PFNGLBINDTEXTUREEXTPROC)load("glBindTextureEXT");
	glad_glDeleteTexturesEXT = (PFNGLDELETETEXTURESEXTPROC)load("glDeleteTexturesEXT");
	glad_glGenTexturesEXT = (PFNGLGENTEXTURESEXTPROC)load("glGenTexturesEXT");
	glad_glIsTextureEXT = (PFNGLISTEXTUREEXTPROC)load("glIsTextureEXT");
	glad_glPrioritizeTexturesEXT = (PFNGLPRIORITIZETEXTURESEXTPROC)load("glPrioritizeTexturesEXT");
}