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
typedef  scalar_t__ PFNGLTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLPOLYGONOFFSETPROC ;
typedef  scalar_t__ PFNGLISTEXTUREPROC ;
typedef  scalar_t__ PFNGLGENTEXTURESPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSPROC ;
typedef  scalar_t__ PFNGLDELETETEXTURESPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOPYTEXIMAGE1DPROC ;
typedef  scalar_t__ PFNGLBINDTEXTUREPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_1 ; 
 scalar_t__ glad_glBindTexture ; 
 scalar_t__ glad_glCopyTexImage1D ; 
 scalar_t__ glad_glCopyTexImage2D ; 
 scalar_t__ glad_glCopyTexSubImage1D ; 
 scalar_t__ glad_glCopyTexSubImage2D ; 
 scalar_t__ glad_glDeleteTextures ; 
 scalar_t__ glad_glDrawArrays ; 
 scalar_t__ glad_glDrawElements ; 
 scalar_t__ glad_glGenTextures ; 
 scalar_t__ glad_glIsTexture ; 
 scalar_t__ glad_glPolygonOffset ; 
 scalar_t__ glad_glTexSubImage1D ; 
 scalar_t__ glad_glTexSubImage2D ; 

__attribute__((used)) static void load_GL_VERSION_1_1(GLADloadproc load) {
	if(!GLAD_GL_VERSION_1_1) return;
	glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load("glDrawArrays");
	glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
	glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)load("glPolygonOffset");
	glad_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)load("glCopyTexImage1D");
	glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)load("glCopyTexImage2D");
	glad_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)load("glCopyTexSubImage1D");
	glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)load("glCopyTexSubImage2D");
	glad_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)load("glTexSubImage1D");
	glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)load("glTexSubImage2D");
	glad_glBindTexture = (PFNGLBINDTEXTUREPROC)load("glBindTexture");
	glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load("glDeleteTextures");
	glad_glGenTextures = (PFNGLGENTEXTURESPROC)load("glGenTextures");
	glad_glIsTexture = (PFNGLISTEXTUREPROC)load("glIsTexture");
}