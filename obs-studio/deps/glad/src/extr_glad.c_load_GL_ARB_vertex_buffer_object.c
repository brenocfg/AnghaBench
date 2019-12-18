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
typedef  scalar_t__ PFNGLUNMAPBUFFERARBPROC ;
typedef  scalar_t__ PFNGLMAPBUFFERARBPROC ;
typedef  scalar_t__ PFNGLISBUFFERARBPROC ;
typedef  scalar_t__ PFNGLGETBUFFERSUBDATAARBPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPOINTERVARBPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPARAMETERIVARBPROC ;
typedef  scalar_t__ PFNGLGENBUFFERSARBPROC ;
typedef  scalar_t__ PFNGLDELETEBUFFERSARBPROC ;
typedef  scalar_t__ PFNGLBUFFERSUBDATAARBPROC ;
typedef  scalar_t__ PFNGLBUFFERDATAARBPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_vertex_buffer_object ; 
 scalar_t__ glad_glBindBufferARB ; 
 scalar_t__ glad_glBufferDataARB ; 
 scalar_t__ glad_glBufferSubDataARB ; 
 scalar_t__ glad_glDeleteBuffersARB ; 
 scalar_t__ glad_glGenBuffersARB ; 
 scalar_t__ glad_glGetBufferParameterivARB ; 
 scalar_t__ glad_glGetBufferPointervARB ; 
 scalar_t__ glad_glGetBufferSubDataARB ; 
 scalar_t__ glad_glIsBufferARB ; 
 scalar_t__ glad_glMapBufferARB ; 
 scalar_t__ glad_glUnmapBufferARB ; 

__attribute__((used)) static void load_GL_ARB_vertex_buffer_object(GLADloadproc load) {
	if(!GLAD_GL_ARB_vertex_buffer_object) return;
	glad_glBindBufferARB = (PFNGLBINDBUFFERARBPROC)load("glBindBufferARB");
	glad_glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)load("glDeleteBuffersARB");
	glad_glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)load("glGenBuffersARB");
	glad_glIsBufferARB = (PFNGLISBUFFERARBPROC)load("glIsBufferARB");
	glad_glBufferDataARB = (PFNGLBUFFERDATAARBPROC)load("glBufferDataARB");
	glad_glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)load("glBufferSubDataARB");
	glad_glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)load("glGetBufferSubDataARB");
	glad_glMapBufferARB = (PFNGLMAPBUFFERARBPROC)load("glMapBufferARB");
	glad_glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)load("glUnmapBufferARB");
	glad_glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)load("glGetBufferParameterivARB");
	glad_glGetBufferPointervARB = (PFNGLGETBUFFERPOINTERVARBPROC)load("glGetBufferPointervARB");
}