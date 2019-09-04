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
typedef  scalar_t__ PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC ;
typedef  scalar_t__ PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC ;
typedef  scalar_t__ PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC ;
typedef  scalar_t__ PFNGLGETVARYINGLOCATIONNVPROC ;
typedef  scalar_t__ PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC ;
typedef  scalar_t__ PFNGLGETACTIVEVARYINGNVPROC ;
typedef  scalar_t__ PFNGLENDTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERRANGENVPROC ;
typedef  scalar_t__ PFNGLBINDBUFFEROFFSETNVPROC ;
typedef  scalar_t__ PFNGLBINDBUFFERBASENVPROC ;
typedef  scalar_t__ PFNGLBEGINTRANSFORMFEEDBACKNVPROC ;
typedef  scalar_t__ PFNGLACTIVEVARYINGNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_transform_feedback ; 
 scalar_t__ glad_glActiveVaryingNV ; 
 scalar_t__ glad_glBeginTransformFeedbackNV ; 
 scalar_t__ glad_glBindBufferBaseNV ; 
 scalar_t__ glad_glBindBufferOffsetNV ; 
 scalar_t__ glad_glBindBufferRangeNV ; 
 scalar_t__ glad_glEndTransformFeedbackNV ; 
 scalar_t__ glad_glGetActiveVaryingNV ; 
 scalar_t__ glad_glGetTransformFeedbackVaryingNV ; 
 scalar_t__ glad_glGetVaryingLocationNV ; 
 scalar_t__ glad_glTransformFeedbackAttribsNV ; 
 scalar_t__ glad_glTransformFeedbackStreamAttribsNV ; 
 scalar_t__ glad_glTransformFeedbackVaryingsNV ; 

__attribute__((used)) static void load_GL_NV_transform_feedback(GLADloadproc load) {
	if(!GLAD_GL_NV_transform_feedback) return;
	glad_glBeginTransformFeedbackNV = (PFNGLBEGINTRANSFORMFEEDBACKNVPROC)load("glBeginTransformFeedbackNV");
	glad_glEndTransformFeedbackNV = (PFNGLENDTRANSFORMFEEDBACKNVPROC)load("glEndTransformFeedbackNV");
	glad_glTransformFeedbackAttribsNV = (PFNGLTRANSFORMFEEDBACKATTRIBSNVPROC)load("glTransformFeedbackAttribsNV");
	glad_glBindBufferRangeNV = (PFNGLBINDBUFFERRANGENVPROC)load("glBindBufferRangeNV");
	glad_glBindBufferOffsetNV = (PFNGLBINDBUFFEROFFSETNVPROC)load("glBindBufferOffsetNV");
	glad_glBindBufferBaseNV = (PFNGLBINDBUFFERBASENVPROC)load("glBindBufferBaseNV");
	glad_glTransformFeedbackVaryingsNV = (PFNGLTRANSFORMFEEDBACKVARYINGSNVPROC)load("glTransformFeedbackVaryingsNV");
	glad_glActiveVaryingNV = (PFNGLACTIVEVARYINGNVPROC)load("glActiveVaryingNV");
	glad_glGetVaryingLocationNV = (PFNGLGETVARYINGLOCATIONNVPROC)load("glGetVaryingLocationNV");
	glad_glGetActiveVaryingNV = (PFNGLGETACTIVEVARYINGNVPROC)load("glGetActiveVaryingNV");
	glad_glGetTransformFeedbackVaryingNV = (PFNGLGETTRANSFORMFEEDBACKVARYINGNVPROC)load("glGetTransformFeedbackVaryingNV");
	glad_glTransformFeedbackStreamAttribsNV = (PFNGLTRANSFORMFEEDBACKSTREAMATTRIBSNVPROC)load("glTransformFeedbackStreamAttribsNV");
}