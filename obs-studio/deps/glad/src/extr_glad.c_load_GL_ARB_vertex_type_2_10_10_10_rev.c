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
typedef  scalar_t__ PFNGLVERTEXP4UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXP4UIPROC ;
typedef  scalar_t__ PFNGLVERTEXP3UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXP3UIPROC ;
typedef  scalar_t__ PFNGLVERTEXP2UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXP2UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP4UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP4UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP3UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP3UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP2UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP2UIPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP1UIVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBP1UIPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP4UIVPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP4UIPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP3UIVPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP3UIPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP2UIVPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP2UIPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP1UIVPROC ;
typedef  scalar_t__ PFNGLTEXCOORDP1UIPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLORP3UIVPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLORP3UIPROC ;
typedef  scalar_t__ PFNGLNORMALP3UIVPROC ;
typedef  scalar_t__ PFNGLNORMALP3UIPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP4UIVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP4UIPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP3UIVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP3UIPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP2UIVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP2UIPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP1UIVPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORDP1UIPROC ;
typedef  scalar_t__ PFNGLCOLORP4UIVPROC ;
typedef  scalar_t__ PFNGLCOLORP4UIPROC ;
typedef  scalar_t__ PFNGLCOLORP3UIVPROC ;
typedef  scalar_t__ PFNGLCOLORP3UIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_vertex_type_2_10_10_10_rev ; 
 scalar_t__ glad_glColorP3ui ; 
 scalar_t__ glad_glColorP3uiv ; 
 scalar_t__ glad_glColorP4ui ; 
 scalar_t__ glad_glColorP4uiv ; 
 scalar_t__ glad_glMultiTexCoordP1ui ; 
 scalar_t__ glad_glMultiTexCoordP1uiv ; 
 scalar_t__ glad_glMultiTexCoordP2ui ; 
 scalar_t__ glad_glMultiTexCoordP2uiv ; 
 scalar_t__ glad_glMultiTexCoordP3ui ; 
 scalar_t__ glad_glMultiTexCoordP3uiv ; 
 scalar_t__ glad_glMultiTexCoordP4ui ; 
 scalar_t__ glad_glMultiTexCoordP4uiv ; 
 scalar_t__ glad_glNormalP3ui ; 
 scalar_t__ glad_glNormalP3uiv ; 
 scalar_t__ glad_glSecondaryColorP3ui ; 
 scalar_t__ glad_glSecondaryColorP3uiv ; 
 scalar_t__ glad_glTexCoordP1ui ; 
 scalar_t__ glad_glTexCoordP1uiv ; 
 scalar_t__ glad_glTexCoordP2ui ; 
 scalar_t__ glad_glTexCoordP2uiv ; 
 scalar_t__ glad_glTexCoordP3ui ; 
 scalar_t__ glad_glTexCoordP3uiv ; 
 scalar_t__ glad_glTexCoordP4ui ; 
 scalar_t__ glad_glTexCoordP4uiv ; 
 scalar_t__ glad_glVertexAttribP1ui ; 
 scalar_t__ glad_glVertexAttribP1uiv ; 
 scalar_t__ glad_glVertexAttribP2ui ; 
 scalar_t__ glad_glVertexAttribP2uiv ; 
 scalar_t__ glad_glVertexAttribP3ui ; 
 scalar_t__ glad_glVertexAttribP3uiv ; 
 scalar_t__ glad_glVertexAttribP4ui ; 
 scalar_t__ glad_glVertexAttribP4uiv ; 
 scalar_t__ glad_glVertexP2ui ; 
 scalar_t__ glad_glVertexP2uiv ; 
 scalar_t__ glad_glVertexP3ui ; 
 scalar_t__ glad_glVertexP3uiv ; 
 scalar_t__ glad_glVertexP4ui ; 
 scalar_t__ glad_glVertexP4uiv ; 

__attribute__((used)) static void load_GL_ARB_vertex_type_2_10_10_10_rev(GLADloadproc load) {
	if(!GLAD_GL_ARB_vertex_type_2_10_10_10_rev) return;
	glad_glVertexAttribP1ui = (PFNGLVERTEXATTRIBP1UIPROC)load("glVertexAttribP1ui");
	glad_glVertexAttribP1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)load("glVertexAttribP1uiv");
	glad_glVertexAttribP2ui = (PFNGLVERTEXATTRIBP2UIPROC)load("glVertexAttribP2ui");
	glad_glVertexAttribP2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)load("glVertexAttribP2uiv");
	glad_glVertexAttribP3ui = (PFNGLVERTEXATTRIBP3UIPROC)load("glVertexAttribP3ui");
	glad_glVertexAttribP3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)load("glVertexAttribP3uiv");
	glad_glVertexAttribP4ui = (PFNGLVERTEXATTRIBP4UIPROC)load("glVertexAttribP4ui");
	glad_glVertexAttribP4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)load("glVertexAttribP4uiv");
	glad_glVertexP2ui = (PFNGLVERTEXP2UIPROC)load("glVertexP2ui");
	glad_glVertexP2uiv = (PFNGLVERTEXP2UIVPROC)load("glVertexP2uiv");
	glad_glVertexP3ui = (PFNGLVERTEXP3UIPROC)load("glVertexP3ui");
	glad_glVertexP3uiv = (PFNGLVERTEXP3UIVPROC)load("glVertexP3uiv");
	glad_glVertexP4ui = (PFNGLVERTEXP4UIPROC)load("glVertexP4ui");
	glad_glVertexP4uiv = (PFNGLVERTEXP4UIVPROC)load("glVertexP4uiv");
	glad_glTexCoordP1ui = (PFNGLTEXCOORDP1UIPROC)load("glTexCoordP1ui");
	glad_glTexCoordP1uiv = (PFNGLTEXCOORDP1UIVPROC)load("glTexCoordP1uiv");
	glad_glTexCoordP2ui = (PFNGLTEXCOORDP2UIPROC)load("glTexCoordP2ui");
	glad_glTexCoordP2uiv = (PFNGLTEXCOORDP2UIVPROC)load("glTexCoordP2uiv");
	glad_glTexCoordP3ui = (PFNGLTEXCOORDP3UIPROC)load("glTexCoordP3ui");
	glad_glTexCoordP3uiv = (PFNGLTEXCOORDP3UIVPROC)load("glTexCoordP3uiv");
	glad_glTexCoordP4ui = (PFNGLTEXCOORDP4UIPROC)load("glTexCoordP4ui");
	glad_glTexCoordP4uiv = (PFNGLTEXCOORDP4UIVPROC)load("glTexCoordP4uiv");
	glad_glMultiTexCoordP1ui = (PFNGLMULTITEXCOORDP1UIPROC)load("glMultiTexCoordP1ui");
	glad_glMultiTexCoordP1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)load("glMultiTexCoordP1uiv");
	glad_glMultiTexCoordP2ui = (PFNGLMULTITEXCOORDP2UIPROC)load("glMultiTexCoordP2ui");
	glad_glMultiTexCoordP2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)load("glMultiTexCoordP2uiv");
	glad_glMultiTexCoordP3ui = (PFNGLMULTITEXCOORDP3UIPROC)load("glMultiTexCoordP3ui");
	glad_glMultiTexCoordP3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)load("glMultiTexCoordP3uiv");
	glad_glMultiTexCoordP4ui = (PFNGLMULTITEXCOORDP4UIPROC)load("glMultiTexCoordP4ui");
	glad_glMultiTexCoordP4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)load("glMultiTexCoordP4uiv");
	glad_glNormalP3ui = (PFNGLNORMALP3UIPROC)load("glNormalP3ui");
	glad_glNormalP3uiv = (PFNGLNORMALP3UIVPROC)load("glNormalP3uiv");
	glad_glColorP3ui = (PFNGLCOLORP3UIPROC)load("glColorP3ui");
	glad_glColorP3uiv = (PFNGLCOLORP3UIVPROC)load("glColorP3uiv");
	glad_glColorP4ui = (PFNGLCOLORP4UIPROC)load("glColorP4ui");
	glad_glColorP4uiv = (PFNGLCOLORP4UIVPROC)load("glColorP4uiv");
	glad_glSecondaryColorP3ui = (PFNGLSECONDARYCOLORP3UIPROC)load("glSecondaryColorP3ui");
	glad_glSecondaryColorP3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)load("glSecondaryColorP3uiv");
}