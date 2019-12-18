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
typedef  scalar_t__ PFNGLPUSHDEBUGGROUPPROC ;
typedef  scalar_t__ PFNGLPUSHDEBUGGROUPKHRPROC ;
typedef  scalar_t__ PFNGLPOPDEBUGGROUPPROC ;
typedef  scalar_t__ PFNGLPOPDEBUGGROUPKHRPROC ;
typedef  scalar_t__ PFNGLOBJECTPTRLABELPROC ;
typedef  scalar_t__ PFNGLOBJECTPTRLABELKHRPROC ;
typedef  scalar_t__ PFNGLOBJECTLABELPROC ;
typedef  scalar_t__ PFNGLOBJECTLABELKHRPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVPROC ;
typedef  scalar_t__ PFNGLGETPOINTERVKHRPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPTRLABELPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPTRLABELKHRPROC ;
typedef  scalar_t__ PFNGLGETOBJECTLABELPROC ;
typedef  scalar_t__ PFNGLGETOBJECTLABELKHRPROC ;
typedef  scalar_t__ PFNGLGETDEBUGMESSAGELOGPROC ;
typedef  scalar_t__ PFNGLGETDEBUGMESSAGELOGKHRPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGEINSERTPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGEINSERTKHRPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECONTROLPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECONTROLKHRPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECALLBACKPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECALLBACKKHRPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_KHR_debug ; 
 scalar_t__ glad_glDebugMessageCallback ; 
 scalar_t__ glad_glDebugMessageCallbackKHR ; 
 scalar_t__ glad_glDebugMessageControl ; 
 scalar_t__ glad_glDebugMessageControlKHR ; 
 scalar_t__ glad_glDebugMessageInsert ; 
 scalar_t__ glad_glDebugMessageInsertKHR ; 
 scalar_t__ glad_glGetDebugMessageLog ; 
 scalar_t__ glad_glGetDebugMessageLogKHR ; 
 scalar_t__ glad_glGetObjectLabel ; 
 scalar_t__ glad_glGetObjectLabelKHR ; 
 scalar_t__ glad_glGetObjectPtrLabel ; 
 scalar_t__ glad_glGetObjectPtrLabelKHR ; 
 scalar_t__ glad_glGetPointerv ; 
 scalar_t__ glad_glGetPointervKHR ; 
 scalar_t__ glad_glObjectLabel ; 
 scalar_t__ glad_glObjectLabelKHR ; 
 scalar_t__ glad_glObjectPtrLabel ; 
 scalar_t__ glad_glObjectPtrLabelKHR ; 
 scalar_t__ glad_glPopDebugGroup ; 
 scalar_t__ glad_glPopDebugGroupKHR ; 
 scalar_t__ glad_glPushDebugGroup ; 
 scalar_t__ glad_glPushDebugGroupKHR ; 

__attribute__((used)) static void load_GL_KHR_debug(GLADloadproc load) {
	if(!GLAD_GL_KHR_debug) return;
	glad_glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)load("glDebugMessageControl");
	glad_glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)load("glDebugMessageInsert");
	glad_glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)load("glDebugMessageCallback");
	glad_glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)load("glGetDebugMessageLog");
	glad_glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)load("glPushDebugGroup");
	glad_glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)load("glPopDebugGroup");
	glad_glObjectLabel = (PFNGLOBJECTLABELPROC)load("glObjectLabel");
	glad_glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)load("glGetObjectLabel");
	glad_glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)load("glObjectPtrLabel");
	glad_glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)load("glGetObjectPtrLabel");
	glad_glGetPointerv = (PFNGLGETPOINTERVPROC)load("glGetPointerv");
	glad_glDebugMessageControlKHR = (PFNGLDEBUGMESSAGECONTROLKHRPROC)load("glDebugMessageControlKHR");
	glad_glDebugMessageInsertKHR = (PFNGLDEBUGMESSAGEINSERTKHRPROC)load("glDebugMessageInsertKHR");
	glad_glDebugMessageCallbackKHR = (PFNGLDEBUGMESSAGECALLBACKKHRPROC)load("glDebugMessageCallbackKHR");
	glad_glGetDebugMessageLogKHR = (PFNGLGETDEBUGMESSAGELOGKHRPROC)load("glGetDebugMessageLogKHR");
	glad_glPushDebugGroupKHR = (PFNGLPUSHDEBUGGROUPKHRPROC)load("glPushDebugGroupKHR");
	glad_glPopDebugGroupKHR = (PFNGLPOPDEBUGGROUPKHRPROC)load("glPopDebugGroupKHR");
	glad_glObjectLabelKHR = (PFNGLOBJECTLABELKHRPROC)load("glObjectLabelKHR");
	glad_glGetObjectLabelKHR = (PFNGLGETOBJECTLABELKHRPROC)load("glGetObjectLabelKHR");
	glad_glObjectPtrLabelKHR = (PFNGLOBJECTPTRLABELKHRPROC)load("glObjectPtrLabelKHR");
	glad_glGetObjectPtrLabelKHR = (PFNGLGETOBJECTPTRLABELKHRPROC)load("glGetObjectPtrLabelKHR");
	glad_glGetPointervKHR = (PFNGLGETPOINTERVKHRPROC)load("glGetPointervKHR");
}