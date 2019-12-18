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
typedef  scalar_t__ PFNGLRESUMETRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLPAUSETRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLISTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLGENTRANSFORMFEEDBACKSNVPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLDELETETRANSFORMFEEDBACKSNVPROC ;
typedef  scalar_t__ PFNGLBINDTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_transform_feedback2 ; 
 scalar_t__ glad_glBindTransformFeedbackNV ; 
 scalar_t__ glad_glDeleteTransformFeedbacksNV ; 
 scalar_t__ glad_glDrawTransformFeedbackNV ; 
 scalar_t__ glad_glGenTransformFeedbacksNV ; 
 scalar_t__ glad_glIsTransformFeedbackNV ; 
 scalar_t__ glad_glPauseTransformFeedbackNV ; 
 scalar_t__ glad_glResumeTransformFeedbackNV ; 

__attribute__((used)) static void load_GL_NV_transform_feedback2(GLADloadproc load) {
	if(!GLAD_GL_NV_transform_feedback2) return;
	glad_glBindTransformFeedbackNV = (PFNGLBINDTRANSFORMFEEDBACKNVPROC)load("glBindTransformFeedbackNV");
	glad_glDeleteTransformFeedbacksNV = (PFNGLDELETETRANSFORMFEEDBACKSNVPROC)load("glDeleteTransformFeedbacksNV");
	glad_glGenTransformFeedbacksNV = (PFNGLGENTRANSFORMFEEDBACKSNVPROC)load("glGenTransformFeedbacksNV");
	glad_glIsTransformFeedbackNV = (PFNGLISTRANSFORMFEEDBACKNVPROC)load("glIsTransformFeedbackNV");
	glad_glPauseTransformFeedbackNV = (PFNGLPAUSETRANSFORMFEEDBACKNVPROC)load("glPauseTransformFeedbackNV");
	glad_glResumeTransformFeedbackNV = (PFNGLRESUMETRANSFORMFEEDBACKNVPROC)load("glResumeTransformFeedbackNV");
	glad_glDrawTransformFeedbackNV = (PFNGLDRAWTRANSFORMFEEDBACKNVPROC)load("glDrawTransformFeedbackNV");
}