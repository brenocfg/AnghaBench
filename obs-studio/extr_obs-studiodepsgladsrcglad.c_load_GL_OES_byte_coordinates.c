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
typedef  scalar_t__ PFNGLVERTEX4BVOESPROC ;
typedef  scalar_t__ PFNGLVERTEX4BOESPROC ;
typedef  scalar_t__ PFNGLVERTEX3BVOESPROC ;
typedef  scalar_t__ PFNGLVERTEX3BOESPROC ;
typedef  scalar_t__ PFNGLVERTEX2BVOESPROC ;
typedef  scalar_t__ PFNGLVERTEX2BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD4BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD4BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD3BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD3BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD2BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD2BOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD1BVOESPROC ;
typedef  scalar_t__ PFNGLTEXCOORD1BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2BOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1BVOESPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1BOESPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_OES_byte_coordinates ; 
 scalar_t__ glad_glMultiTexCoord1bOES ; 
 scalar_t__ glad_glMultiTexCoord1bvOES ; 
 scalar_t__ glad_glMultiTexCoord2bOES ; 
 scalar_t__ glad_glMultiTexCoord2bvOES ; 
 scalar_t__ glad_glMultiTexCoord3bOES ; 
 scalar_t__ glad_glMultiTexCoord3bvOES ; 
 scalar_t__ glad_glMultiTexCoord4bOES ; 
 scalar_t__ glad_glMultiTexCoord4bvOES ; 
 scalar_t__ glad_glTexCoord1bOES ; 
 scalar_t__ glad_glTexCoord1bvOES ; 
 scalar_t__ glad_glTexCoord2bOES ; 
 scalar_t__ glad_glTexCoord2bvOES ; 
 scalar_t__ glad_glTexCoord3bOES ; 
 scalar_t__ glad_glTexCoord3bvOES ; 
 scalar_t__ glad_glTexCoord4bOES ; 
 scalar_t__ glad_glTexCoord4bvOES ; 
 scalar_t__ glad_glVertex2bOES ; 
 scalar_t__ glad_glVertex2bvOES ; 
 scalar_t__ glad_glVertex3bOES ; 
 scalar_t__ glad_glVertex3bvOES ; 
 scalar_t__ glad_glVertex4bOES ; 
 scalar_t__ glad_glVertex4bvOES ; 

__attribute__((used)) static void load_GL_OES_byte_coordinates(GLADloadproc load) {
	if(!GLAD_GL_OES_byte_coordinates) return;
	glad_glMultiTexCoord1bOES = (PFNGLMULTITEXCOORD1BOESPROC)load("glMultiTexCoord1bOES");
	glad_glMultiTexCoord1bvOES = (PFNGLMULTITEXCOORD1BVOESPROC)load("glMultiTexCoord1bvOES");
	glad_glMultiTexCoord2bOES = (PFNGLMULTITEXCOORD2BOESPROC)load("glMultiTexCoord2bOES");
	glad_glMultiTexCoord2bvOES = (PFNGLMULTITEXCOORD2BVOESPROC)load("glMultiTexCoord2bvOES");
	glad_glMultiTexCoord3bOES = (PFNGLMULTITEXCOORD3BOESPROC)load("glMultiTexCoord3bOES");
	glad_glMultiTexCoord3bvOES = (PFNGLMULTITEXCOORD3BVOESPROC)load("glMultiTexCoord3bvOES");
	glad_glMultiTexCoord4bOES = (PFNGLMULTITEXCOORD4BOESPROC)load("glMultiTexCoord4bOES");
	glad_glMultiTexCoord4bvOES = (PFNGLMULTITEXCOORD4BVOESPROC)load("glMultiTexCoord4bvOES");
	glad_glTexCoord1bOES = (PFNGLTEXCOORD1BOESPROC)load("glTexCoord1bOES");
	glad_glTexCoord1bvOES = (PFNGLTEXCOORD1BVOESPROC)load("glTexCoord1bvOES");
	glad_glTexCoord2bOES = (PFNGLTEXCOORD2BOESPROC)load("glTexCoord2bOES");
	glad_glTexCoord2bvOES = (PFNGLTEXCOORD2BVOESPROC)load("glTexCoord2bvOES");
	glad_glTexCoord3bOES = (PFNGLTEXCOORD3BOESPROC)load("glTexCoord3bOES");
	glad_glTexCoord3bvOES = (PFNGLTEXCOORD3BVOESPROC)load("glTexCoord3bvOES");
	glad_glTexCoord4bOES = (PFNGLTEXCOORD4BOESPROC)load("glTexCoord4bOES");
	glad_glTexCoord4bvOES = (PFNGLTEXCOORD4BVOESPROC)load("glTexCoord4bvOES");
	glad_glVertex2bOES = (PFNGLVERTEX2BOESPROC)load("glVertex2bOES");
	glad_glVertex2bvOES = (PFNGLVERTEX2BVOESPROC)load("glVertex2bvOES");
	glad_glVertex3bOES = (PFNGLVERTEX3BOESPROC)load("glVertex3bOES");
	glad_glVertex3bvOES = (PFNGLVERTEX3BVOESPROC)load("glVertex3bvOES");
	glad_glVertex4bOES = (PFNGLVERTEX4BOESPROC)load("glVertex4bOES");
	glad_glVertex4bvOES = (PFNGLVERTEX4BVOESPROC)load("glVertex4bvOES");
}