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
typedef  scalar_t__ PFNGLORTHOFOESPROC ;
typedef  scalar_t__ PFNGLGETCLIPPLANEFOESPROC ;
typedef  scalar_t__ PFNGLFRUSTUMFOESPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEFOESPROC ;
typedef  scalar_t__ PFNGLCLIPPLANEFOESPROC ;
typedef  scalar_t__ PFNGLCLEARDEPTHFOESPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_OES_single_precision ; 
 scalar_t__ glad_glClearDepthfOES ; 
 scalar_t__ glad_glClipPlanefOES ; 
 scalar_t__ glad_glDepthRangefOES ; 
 scalar_t__ glad_glFrustumfOES ; 
 scalar_t__ glad_glGetClipPlanefOES ; 
 scalar_t__ glad_glOrthofOES ; 

__attribute__((used)) static void load_GL_OES_single_precision(GLADloadproc load) {
	if(!GLAD_GL_OES_single_precision) return;
	glad_glClearDepthfOES = (PFNGLCLEARDEPTHFOESPROC)load("glClearDepthfOES");
	glad_glClipPlanefOES = (PFNGLCLIPPLANEFOESPROC)load("glClipPlanefOES");
	glad_glDepthRangefOES = (PFNGLDEPTHRANGEFOESPROC)load("glDepthRangefOES");
	glad_glFrustumfOES = (PFNGLFRUSTUMFOESPROC)load("glFrustumfOES");
	glad_glGetClipPlanefOES = (PFNGLGETCLIPPLANEFOESPROC)load("glGetClipPlanefOES");
	glad_glOrthofOES = (PFNGLORTHOFOESPROC)load("glOrthofOES");
}