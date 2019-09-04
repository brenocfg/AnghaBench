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
typedef  scalar_t__ PFNGLRENDERBUFFERSTORAGEPROC ;
typedef  scalar_t__ PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLISRENDERBUFFERPROC ;
typedef  scalar_t__ PFNGLISFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLGETRENDERBUFFERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGENRENDERBUFFERSPROC ;
typedef  scalar_t__ PFNGLGENFRAMEBUFFERSPROC ;
typedef  scalar_t__ PFNGLGENERATEMIPMAPPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURELAYERPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURE3DPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURE2DPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURE1DPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERRENDERBUFFERPROC ;
typedef  scalar_t__ PFNGLDELETERENDERBUFFERSPROC ;
typedef  scalar_t__ PFNGLDELETEFRAMEBUFFERSPROC ;
typedef  scalar_t__ PFNGLCHECKFRAMEBUFFERSTATUSPROC ;
typedef  scalar_t__ PFNGLBLITFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLBINDRENDERBUFFERPROC ;
typedef  scalar_t__ PFNGLBINDFRAMEBUFFERPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_framebuffer_object ; 
 scalar_t__ glad_glBindFramebuffer ; 
 scalar_t__ glad_glBindRenderbuffer ; 
 scalar_t__ glad_glBlitFramebuffer ; 
 scalar_t__ glad_glCheckFramebufferStatus ; 
 scalar_t__ glad_glDeleteFramebuffers ; 
 scalar_t__ glad_glDeleteRenderbuffers ; 
 scalar_t__ glad_glFramebufferRenderbuffer ; 
 scalar_t__ glad_glFramebufferTexture1D ; 
 scalar_t__ glad_glFramebufferTexture2D ; 
 scalar_t__ glad_glFramebufferTexture3D ; 
 scalar_t__ glad_glFramebufferTextureLayer ; 
 scalar_t__ glad_glGenFramebuffers ; 
 scalar_t__ glad_glGenRenderbuffers ; 
 scalar_t__ glad_glGenerateMipmap ; 
 scalar_t__ glad_glGetFramebufferAttachmentParameteriv ; 
 scalar_t__ glad_glGetRenderbufferParameteriv ; 
 scalar_t__ glad_glIsFramebuffer ; 
 scalar_t__ glad_glIsRenderbuffer ; 
 scalar_t__ glad_glRenderbufferStorage ; 
 scalar_t__ glad_glRenderbufferStorageMultisample ; 

__attribute__((used)) static void load_GL_ARB_framebuffer_object(GLADloadproc load) {
	if(!GLAD_GL_ARB_framebuffer_object) return;
	glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)load("glIsRenderbuffer");
	glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)load("glBindRenderbuffer");
	glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)load("glDeleteRenderbuffers");
	glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)load("glGenRenderbuffers");
	glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)load("glRenderbufferStorage");
	glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)load("glGetRenderbufferParameteriv");
	glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)load("glIsFramebuffer");
	glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)load("glBindFramebuffer");
	glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)load("glDeleteFramebuffers");
	glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)load("glGenFramebuffers");
	glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load("glCheckFramebufferStatus");
	glad_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)load("glFramebufferTexture1D");
	glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load("glFramebufferTexture2D");
	glad_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)load("glFramebufferTexture3D");
	glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)load("glFramebufferRenderbuffer");
	glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)load("glGetFramebufferAttachmentParameteriv");
	glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)load("glGenerateMipmap");
	glad_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)load("glBlitFramebuffer");
	glad_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)load("glRenderbufferStorageMultisample");
	glad_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)load("glFramebufferTextureLayer");
}