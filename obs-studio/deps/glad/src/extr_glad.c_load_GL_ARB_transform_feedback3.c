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
typedef  scalar_t__ PFNGLGETQUERYINDEXEDIVPROC ;
typedef  scalar_t__ PFNGLENDQUERYINDEXEDPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC ;
typedef  scalar_t__ PFNGLBEGINQUERYINDEXEDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_transform_feedback3 ; 
 scalar_t__ glad_glBeginQueryIndexed ; 
 scalar_t__ glad_glDrawTransformFeedbackStream ; 
 scalar_t__ glad_glEndQueryIndexed ; 
 scalar_t__ glad_glGetQueryIndexediv ; 

__attribute__((used)) static void load_GL_ARB_transform_feedback3(GLADloadproc load) {
	if(!GLAD_GL_ARB_transform_feedback3) return;
	glad_glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)load("glDrawTransformFeedbackStream");
	glad_glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)load("glBeginQueryIndexed");
	glad_glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)load("glEndQueryIndexed");
	glad_glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)load("glGetQueryIndexediv");
}