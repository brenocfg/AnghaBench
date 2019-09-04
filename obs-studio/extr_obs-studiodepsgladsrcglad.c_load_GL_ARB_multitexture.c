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
typedef  scalar_t__ PFNGLMULTITEXCOORD4SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD4DARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD3DARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD2DARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1SARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1IARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1FARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DVARBPROC ;
typedef  scalar_t__ PFNGLMULTITEXCOORD1DARBPROC ;
typedef  scalar_t__ PFNGLCLIENTACTIVETEXTUREARBPROC ;
typedef  scalar_t__ PFNGLACTIVETEXTUREARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_multitexture ; 
 scalar_t__ glad_glActiveTextureARB ; 
 scalar_t__ glad_glClientActiveTextureARB ; 
 scalar_t__ glad_glMultiTexCoord1dARB ; 
 scalar_t__ glad_glMultiTexCoord1dvARB ; 
 scalar_t__ glad_glMultiTexCoord1fARB ; 
 scalar_t__ glad_glMultiTexCoord1fvARB ; 
 scalar_t__ glad_glMultiTexCoord1iARB ; 
 scalar_t__ glad_glMultiTexCoord1ivARB ; 
 scalar_t__ glad_glMultiTexCoord1sARB ; 
 scalar_t__ glad_glMultiTexCoord1svARB ; 
 scalar_t__ glad_glMultiTexCoord2dARB ; 
 scalar_t__ glad_glMultiTexCoord2dvARB ; 
 scalar_t__ glad_glMultiTexCoord2fARB ; 
 scalar_t__ glad_glMultiTexCoord2fvARB ; 
 scalar_t__ glad_glMultiTexCoord2iARB ; 
 scalar_t__ glad_glMultiTexCoord2ivARB ; 
 scalar_t__ glad_glMultiTexCoord2sARB ; 
 scalar_t__ glad_glMultiTexCoord2svARB ; 
 scalar_t__ glad_glMultiTexCoord3dARB ; 
 scalar_t__ glad_glMultiTexCoord3dvARB ; 
 scalar_t__ glad_glMultiTexCoord3fARB ; 
 scalar_t__ glad_glMultiTexCoord3fvARB ; 
 scalar_t__ glad_glMultiTexCoord3iARB ; 
 scalar_t__ glad_glMultiTexCoord3ivARB ; 
 scalar_t__ glad_glMultiTexCoord3sARB ; 
 scalar_t__ glad_glMultiTexCoord3svARB ; 
 scalar_t__ glad_glMultiTexCoord4dARB ; 
 scalar_t__ glad_glMultiTexCoord4dvARB ; 
 scalar_t__ glad_glMultiTexCoord4fARB ; 
 scalar_t__ glad_glMultiTexCoord4fvARB ; 
 scalar_t__ glad_glMultiTexCoord4iARB ; 
 scalar_t__ glad_glMultiTexCoord4ivARB ; 
 scalar_t__ glad_glMultiTexCoord4sARB ; 
 scalar_t__ glad_glMultiTexCoord4svARB ; 

__attribute__((used)) static void load_GL_ARB_multitexture(GLADloadproc load) {
	if(!GLAD_GL_ARB_multitexture) return;
	glad_glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)load("glActiveTextureARB");
	glad_glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)load("glClientActiveTextureARB");
	glad_glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC)load("glMultiTexCoord1dARB");
	glad_glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC)load("glMultiTexCoord1dvARB");
	glad_glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC)load("glMultiTexCoord1fARB");
	glad_glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC)load("glMultiTexCoord1fvARB");
	glad_glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC)load("glMultiTexCoord1iARB");
	glad_glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC)load("glMultiTexCoord1ivARB");
	glad_glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC)load("glMultiTexCoord1sARB");
	glad_glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC)load("glMultiTexCoord1svARB");
	glad_glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC)load("glMultiTexCoord2dARB");
	glad_glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC)load("glMultiTexCoord2dvARB");
	glad_glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)load("glMultiTexCoord2fARB");
	glad_glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC)load("glMultiTexCoord2fvARB");
	glad_glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC)load("glMultiTexCoord2iARB");
	glad_glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC)load("glMultiTexCoord2ivARB");
	glad_glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC)load("glMultiTexCoord2sARB");
	glad_glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC)load("glMultiTexCoord2svARB");
	glad_glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC)load("glMultiTexCoord3dARB");
	glad_glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC)load("glMultiTexCoord3dvARB");
	glad_glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC)load("glMultiTexCoord3fARB");
	glad_glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC)load("glMultiTexCoord3fvARB");
	glad_glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC)load("glMultiTexCoord3iARB");
	glad_glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC)load("glMultiTexCoord3ivARB");
	glad_glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC)load("glMultiTexCoord3sARB");
	glad_glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC)load("glMultiTexCoord3svARB");
	glad_glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC)load("glMultiTexCoord4dARB");
	glad_glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC)load("glMultiTexCoord4dvARB");
	glad_glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC)load("glMultiTexCoord4fARB");
	glad_glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC)load("glMultiTexCoord4fvARB");
	glad_glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC)load("glMultiTexCoord4iARB");
	glad_glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC)load("glMultiTexCoord4ivARB");
	glad_glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC)load("glMultiTexCoord4sARB");
	glad_glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC)load("glMultiTexCoord4svARB");
}