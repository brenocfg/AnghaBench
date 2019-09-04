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
typedef  scalar_t__ PFNGLVERTEXPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLINDEXPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVEXTPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSEXTPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLARRAYELEMENTEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_vertex_array ; 
 scalar_t__ glad_glArrayElementEXT ; 
 scalar_t__ glad_glColorPointerEXT ; 
 scalar_t__ glad_glDrawArraysEXT ; 
 scalar_t__ glad_glEdgeFlagPointerEXT ; 
 scalar_t__ glad_glGetPointervEXT ; 
 scalar_t__ glad_glIndexPointerEXT ; 
 scalar_t__ glad_glNormalPointerEXT ; 
 scalar_t__ glad_glTexCoordPointerEXT ; 
 scalar_t__ glad_glVertexPointerEXT ; 

__attribute__((used)) static void load_GL_EXT_vertex_array(GLADloadproc load) {
	if(!GLAD_GL_EXT_vertex_array) return;
	glad_glArrayElementEXT = (PFNGLARRAYELEMENTEXTPROC)load("glArrayElementEXT");
	glad_glColorPointerEXT = (PFNGLCOLORPOINTEREXTPROC)load("glColorPointerEXT");
	glad_glDrawArraysEXT = (PFNGLDRAWARRAYSEXTPROC)load("glDrawArraysEXT");
	glad_glEdgeFlagPointerEXT = (PFNGLEDGEFLAGPOINTEREXTPROC)load("glEdgeFlagPointerEXT");
	glad_glGetPointervEXT = (PFNGLGETPOINTERVEXTPROC)load("glGetPointervEXT");
	glad_glIndexPointerEXT = (PFNGLINDEXPOINTEREXTPROC)load("glIndexPointerEXT");
	glad_glNormalPointerEXT = (PFNGLNORMALPOINTEREXTPROC)load("glNormalPointerEXT");
	glad_glTexCoordPointerEXT = (PFNGLTEXCOORDPOINTEREXTPROC)load("glTexCoordPointerEXT");
	glad_glVertexPointerEXT = (PFNGLVERTEXPOINTEREXTPROC)load("glVertexPointerEXT");
}