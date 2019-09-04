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
typedef  scalar_t__ PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLELEMENTPOINTERAPPLEPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTARRAYAPPLEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_APPLE_element_array ; 
 scalar_t__ glad_glDrawElementArrayAPPLE ; 
 scalar_t__ glad_glDrawRangeElementArrayAPPLE ; 
 scalar_t__ glad_glElementPointerAPPLE ; 
 scalar_t__ glad_glMultiDrawElementArrayAPPLE ; 
 scalar_t__ glad_glMultiDrawRangeElementArrayAPPLE ; 

__attribute__((used)) static void load_GL_APPLE_element_array(GLADloadproc load) {
	if(!GLAD_GL_APPLE_element_array) return;
	glad_glElementPointerAPPLE = (PFNGLELEMENTPOINTERAPPLEPROC)load("glElementPointerAPPLE");
	glad_glDrawElementArrayAPPLE = (PFNGLDRAWELEMENTARRAYAPPLEPROC)load("glDrawElementArrayAPPLE");
	glad_glDrawRangeElementArrayAPPLE = (PFNGLDRAWRANGEELEMENTARRAYAPPLEPROC)load("glDrawRangeElementArrayAPPLE");
	glad_glMultiDrawElementArrayAPPLE = (PFNGLMULTIDRAWELEMENTARRAYAPPLEPROC)load("glMultiDrawElementArrayAPPLE");
	glad_glMultiDrawRangeElementArrayAPPLE = (PFNGLMULTIDRAWRANGEELEMENTARRAYAPPLEPROC)load("glMultiDrawRangeElementArrayAPPLE");
}