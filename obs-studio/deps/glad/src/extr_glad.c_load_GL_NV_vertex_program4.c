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
typedef  scalar_t__ PFNGLVERTEXATTRIBIPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4USVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4UBVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4SVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4IEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI4BVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI3IEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI2IEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1UIVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1UIEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1IVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBI1IEXTPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBIUIVEXTPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBIIVEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_vertex_program4 ; 
 scalar_t__ glad_glGetVertexAttribIivEXT ; 
 scalar_t__ glad_glGetVertexAttribIuivEXT ; 
 scalar_t__ glad_glVertexAttribI1iEXT ; 
 scalar_t__ glad_glVertexAttribI1ivEXT ; 
 scalar_t__ glad_glVertexAttribI1uiEXT ; 
 scalar_t__ glad_glVertexAttribI1uivEXT ; 
 scalar_t__ glad_glVertexAttribI2iEXT ; 
 scalar_t__ glad_glVertexAttribI2ivEXT ; 
 scalar_t__ glad_glVertexAttribI2uiEXT ; 
 scalar_t__ glad_glVertexAttribI2uivEXT ; 
 scalar_t__ glad_glVertexAttribI3iEXT ; 
 scalar_t__ glad_glVertexAttribI3ivEXT ; 
 scalar_t__ glad_glVertexAttribI3uiEXT ; 
 scalar_t__ glad_glVertexAttribI3uivEXT ; 
 scalar_t__ glad_glVertexAttribI4bvEXT ; 
 scalar_t__ glad_glVertexAttribI4iEXT ; 
 scalar_t__ glad_glVertexAttribI4ivEXT ; 
 scalar_t__ glad_glVertexAttribI4svEXT ; 
 scalar_t__ glad_glVertexAttribI4ubvEXT ; 
 scalar_t__ glad_glVertexAttribI4uiEXT ; 
 scalar_t__ glad_glVertexAttribI4uivEXT ; 
 scalar_t__ glad_glVertexAttribI4usvEXT ; 
 scalar_t__ glad_glVertexAttribIPointerEXT ; 

__attribute__((used)) static void load_GL_NV_vertex_program4(GLADloadproc load) {
	if(!GLAD_GL_NV_vertex_program4) return;
	glad_glVertexAttribI1iEXT = (PFNGLVERTEXATTRIBI1IEXTPROC)load("glVertexAttribI1iEXT");
	glad_glVertexAttribI2iEXT = (PFNGLVERTEXATTRIBI2IEXTPROC)load("glVertexAttribI2iEXT");
	glad_glVertexAttribI3iEXT = (PFNGLVERTEXATTRIBI3IEXTPROC)load("glVertexAttribI3iEXT");
	glad_glVertexAttribI4iEXT = (PFNGLVERTEXATTRIBI4IEXTPROC)load("glVertexAttribI4iEXT");
	glad_glVertexAttribI1uiEXT = (PFNGLVERTEXATTRIBI1UIEXTPROC)load("glVertexAttribI1uiEXT");
	glad_glVertexAttribI2uiEXT = (PFNGLVERTEXATTRIBI2UIEXTPROC)load("glVertexAttribI2uiEXT");
	glad_glVertexAttribI3uiEXT = (PFNGLVERTEXATTRIBI3UIEXTPROC)load("glVertexAttribI3uiEXT");
	glad_glVertexAttribI4uiEXT = (PFNGLVERTEXATTRIBI4UIEXTPROC)load("glVertexAttribI4uiEXT");
	glad_glVertexAttribI1ivEXT = (PFNGLVERTEXATTRIBI1IVEXTPROC)load("glVertexAttribI1ivEXT");
	glad_glVertexAttribI2ivEXT = (PFNGLVERTEXATTRIBI2IVEXTPROC)load("glVertexAttribI2ivEXT");
	glad_glVertexAttribI3ivEXT = (PFNGLVERTEXATTRIBI3IVEXTPROC)load("glVertexAttribI3ivEXT");
	glad_glVertexAttribI4ivEXT = (PFNGLVERTEXATTRIBI4IVEXTPROC)load("glVertexAttribI4ivEXT");
	glad_glVertexAttribI1uivEXT = (PFNGLVERTEXATTRIBI1UIVEXTPROC)load("glVertexAttribI1uivEXT");
	glad_glVertexAttribI2uivEXT = (PFNGLVERTEXATTRIBI2UIVEXTPROC)load("glVertexAttribI2uivEXT");
	glad_glVertexAttribI3uivEXT = (PFNGLVERTEXATTRIBI3UIVEXTPROC)load("glVertexAttribI3uivEXT");
	glad_glVertexAttribI4uivEXT = (PFNGLVERTEXATTRIBI4UIVEXTPROC)load("glVertexAttribI4uivEXT");
	glad_glVertexAttribI4bvEXT = (PFNGLVERTEXATTRIBI4BVEXTPROC)load("glVertexAttribI4bvEXT");
	glad_glVertexAttribI4svEXT = (PFNGLVERTEXATTRIBI4SVEXTPROC)load("glVertexAttribI4svEXT");
	glad_glVertexAttribI4ubvEXT = (PFNGLVERTEXATTRIBI4UBVEXTPROC)load("glVertexAttribI4ubvEXT");
	glad_glVertexAttribI4usvEXT = (PFNGLVERTEXATTRIBI4USVEXTPROC)load("glVertexAttribI4usvEXT");
	glad_glVertexAttribIPointerEXT = (PFNGLVERTEXATTRIBIPOINTEREXTPROC)load("glVertexAttribIPointerEXT");
	glad_glGetVertexAttribIivEXT = (PFNGLGETVERTEXATTRIBIIVEXTPROC)load("glGetVertexAttribIivEXT");
	glad_glGetVertexAttribIuivEXT = (PFNGLGETVERTEXATTRIBIUIVEXTPROC)load("glGetVertexAttribIuivEXT");
}