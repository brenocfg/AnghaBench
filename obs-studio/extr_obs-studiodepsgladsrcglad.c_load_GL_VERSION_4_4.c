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
typedef  scalar_t__ PFNGLCLEARTEXSUBIMAGEPROC ;
typedef  scalar_t__ PFNGLCLEARTEXIMAGEPROC ;
typedef  scalar_t__ PFNGLBUFFERSTORAGEPROC ;
typedef  scalar_t__ PFNGLBINDVERTEXBUFFERSPROC ;
typedef  scalar_t__ PFNGLBINDTEXTURESPROC ;
typedef  scalar_t__ PFNGLBINDSAMPLERSPROC ;
typedef  scalar_t__ PFNGLBINDIMAGETEXTURESPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERSRANGEPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERSBASEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_4_4 ; 
 scalar_t__ glad_glBindBuffersBase ; 
 scalar_t__ glad_glBindBuffersRange ; 
 scalar_t__ glad_glBindImageTextures ; 
 scalar_t__ glad_glBindSamplers ; 
 scalar_t__ glad_glBindTextures ; 
 scalar_t__ glad_glBindVertexBuffers ; 
 scalar_t__ glad_glBufferStorage ; 
 scalar_t__ glad_glClearTexImage ; 
 scalar_t__ glad_glClearTexSubImage ; 

__attribute__((used)) static void load_GL_VERSION_4_4(GLADloadproc load) {
	if(!GLAD_GL_VERSION_4_4) return;
	glad_glBufferStorage = (PFNGLBUFFERSTORAGEPROC)load("glBufferStorage");
	glad_glClearTexImage = (PFNGLCLEARTEXIMAGEPROC)load("glClearTexImage");
	glad_glClearTexSubImage = (PFNGLCLEARTEXSUBIMAGEPROC)load("glClearTexSubImage");
	glad_glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)load("glBindBuffersBase");
	glad_glBindBuffersRange = (PFNGLBINDBUFFERSRANGEPROC)load("glBindBuffersRange");
	glad_glBindTextures = (PFNGLBINDTEXTURESPROC)load("glBindTextures");
	glad_glBindSamplers = (PFNGLBINDSAMPLERSPROC)load("glBindSamplers");
	glad_glBindImageTextures = (PFNGLBINDIMAGETEXTURESPROC)load("glBindImageTextures");
	glad_glBindVertexBuffers = (PFNGLBINDVERTEXBUFFERSPROC)load("glBindVertexBuffers");
}