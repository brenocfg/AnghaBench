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
typedef  scalar_t__ PFNGLRESUMETRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLPAUSETRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLISTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLGENTRANSFORMFEEDBACKSPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLDELETETRANSFORMFEEDBACKSPROC ;
typedef  scalar_t__ PFNGLBINDTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_transform_feedback2 ; 
 scalar_t__ glad_glBindTransformFeedback ; 
 scalar_t__ glad_glDeleteTransformFeedbacks ; 
 scalar_t__ glad_glDrawTransformFeedback ; 
 scalar_t__ glad_glGenTransformFeedbacks ; 
 scalar_t__ glad_glIsTransformFeedback ; 
 scalar_t__ glad_glPauseTransformFeedback ; 
 scalar_t__ glad_glResumeTransformFeedback ; 

__attribute__((used)) static void load_GL_ARB_transform_feedback2(GLADloadproc load) {
	if(!GLAD_GL_ARB_transform_feedback2) return;
	glad_glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)load("glBindTransformFeedback");
	glad_glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)load("glDeleteTransformFeedbacks");
	glad_glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)load("glGenTransformFeedbacks");
	glad_glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)load("glIsTransformFeedback");
	glad_glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)load("glPauseTransformFeedback");
	glad_glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)load("glResumeTransformFeedback");
	glad_glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)load("glDrawTransformFeedback");
}