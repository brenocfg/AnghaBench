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
typedef  scalar_t__ PFNGLWAITSYNCPROC ;
typedef  scalar_t__ PFNGLISSYNCPROC ;
typedef  scalar_t__ PFNGLGETSYNCIVPROC ;
typedef  scalar_t__ PFNGLGETINTEGER64VPROC ;
typedef  scalar_t__ PFNGLFENCESYNCPROC ;
typedef  scalar_t__ PFNGLDELETESYNCPROC ;
typedef  scalar_t__ PFNGLCLIENTWAITSYNCPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_sync ; 
 scalar_t__ glad_glClientWaitSync ; 
 scalar_t__ glad_glDeleteSync ; 
 scalar_t__ glad_glFenceSync ; 
 scalar_t__ glad_glGetInteger64v ; 
 scalar_t__ glad_glGetSynciv ; 
 scalar_t__ glad_glIsSync ; 
 scalar_t__ glad_glWaitSync ; 

__attribute__((used)) static void load_GL_ARB_sync(GLADloadproc load) {
	if(!GLAD_GL_ARB_sync) return;
	glad_glFenceSync = (PFNGLFENCESYNCPROC)load("glFenceSync");
	glad_glIsSync = (PFNGLISSYNCPROC)load("glIsSync");
	glad_glDeleteSync = (PFNGLDELETESYNCPROC)load("glDeleteSync");
	glad_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC)load("glClientWaitSync");
	glad_glWaitSync = (PFNGLWAITSYNCPROC)load("glWaitSync");
	glad_glGetInteger64v = (PFNGLGETINTEGER64VPROC)load("glGetInteger64v");
	glad_glGetSynciv = (PFNGLGETSYNCIVPROC)load("glGetSynciv");
}