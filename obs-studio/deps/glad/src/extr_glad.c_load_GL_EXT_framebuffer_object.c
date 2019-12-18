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
typedef  scalar_t__ PFNGLRENDERBUFFERSTORAGEEXTPROC ;
typedef  scalar_t__ PFNGLISRENDERBUFFEREXTPROC ;
typedef  scalar_t__ PFNGLISFRAMEBUFFEREXTPROC ;
typedef  scalar_t__ PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGENRENDERBUFFERSEXTPROC ;
typedef  scalar_t__ PFNGLGENFRAMEBUFFERSEXTPROC ;
typedef  scalar_t__ PFNGLGENERATEMIPMAPEXTPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURE3DEXTPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURE2DEXTPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURE1DEXTPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC ;
typedef  scalar_t__ PFNGLDELETERENDERBUFFERSEXTPROC ;
typedef  scalar_t__ PFNGLDELETEFRAMEBUFFERSEXTPROC ;
typedef  scalar_t__ PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC ;
typedef  scalar_t__ PFNGLBINDRENDERBUFFEREXTPROC ;
typedef  scalar_t__ PFNGLBINDFRAMEBUFFEREXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_framebuffer_object ; 
 scalar_t__ glad_glBindFramebufferEXT ; 
 scalar_t__ glad_glBindRenderbufferEXT ; 
 scalar_t__ glad_glCheckFramebufferStatusEXT ; 
 scalar_t__ glad_glDeleteFramebuffersEXT ; 
 scalar_t__ glad_glDeleteRenderbuffersEXT ; 
 scalar_t__ glad_glFramebufferRenderbufferEXT ; 
 scalar_t__ glad_glFramebufferTexture1DEXT ; 
 scalar_t__ glad_glFramebufferTexture2DEXT ; 
 scalar_t__ glad_glFramebufferTexture3DEXT ; 
 scalar_t__ glad_glGenFramebuffersEXT ; 
 scalar_t__ glad_glGenRenderbuffersEXT ; 
 scalar_t__ glad_glGenerateMipmapEXT ; 
 scalar_t__ glad_glGetFramebufferAttachmentParameterivEXT ; 
 scalar_t__ glad_glGetRenderbufferParameterivEXT ; 
 scalar_t__ glad_glIsFramebufferEXT ; 
 scalar_t__ glad_glIsRenderbufferEXT ; 
 scalar_t__ glad_glRenderbufferStorageEXT ; 

__attribute__((used)) static void load_GL_EXT_framebuffer_object(GLADloadproc load) {
	if(!GLAD_GL_EXT_framebuffer_object) return;
	glad_glIsRenderbufferEXT = (PFNGLISRENDERBUFFEREXTPROC)load("glIsRenderbufferEXT");
	glad_glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)load("glBindRenderbufferEXT");
	glad_glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)load("glDeleteRenderbuffersEXT");
	glad_glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)load("glGenRenderbuffersEXT");
	glad_glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)load("glRenderbufferStorageEXT");
	glad_glGetRenderbufferParameterivEXT = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC)load("glGetRenderbufferParameterivEXT");
	glad_glIsFramebufferEXT = (PFNGLISFRAMEBUFFEREXTPROC)load("glIsFramebufferEXT");
	glad_glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)load("glBindFramebufferEXT");
	glad_glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)load("glDeleteFramebuffersEXT");
	glad_glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)load("glGenFramebuffersEXT");
	glad_glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)load("glCheckFramebufferStatusEXT");
	glad_glFramebufferTexture1DEXT = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)load("glFramebufferTexture1DEXT");
	glad_glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)load("glFramebufferTexture2DEXT");
	glad_glFramebufferTexture3DEXT = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)load("glFramebufferTexture3DEXT");
	glad_glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)load("glFramebufferRenderbufferEXT");
	glad_glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC)load("glGetFramebufferAttachmentParameterivEXT");
	glad_glGenerateMipmapEXT = (PFNGLGENERATEMIPMAPEXTPROC)load("glGenerateMipmapEXT");
}