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
typedef  scalar_t__ PFNGLSAMPLEPATTERNEXTPROC ;
typedef  scalar_t__ PFNGLSAMPLEMASKEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_multisample ; 
 scalar_t__ glad_glSampleMaskEXT ; 
 scalar_t__ glad_glSamplePatternEXT ; 

__attribute__((used)) static void load_GL_EXT_multisample(GLADloadproc load) {
	if(!GLAD_GL_EXT_multisample) return;
	glad_glSampleMaskEXT = (PFNGLSAMPLEMASKEXTPROC)load("glSampleMaskEXT");
	glad_glSamplePatternEXT = (PFNGLSAMPLEPATTERNEXTPROC)load("glSamplePatternEXT");
}