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
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_transform_feedback_instanced ; 
 scalar_t__ glad_glDrawTransformFeedbackInstanced ; 
 scalar_t__ glad_glDrawTransformFeedbackStreamInstanced ; 

__attribute__((used)) static void load_GL_ARB_transform_feedback_instanced(GLADloadproc load) {
	if(!GLAD_GL_ARB_transform_feedback_instanced) return;
	glad_glDrawTransformFeedbackInstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)load("glDrawTransformFeedbackInstanced");
	glad_glDrawTransformFeedbackStreamInstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)load("glDrawTransformFeedbackStreamInstanced");
}