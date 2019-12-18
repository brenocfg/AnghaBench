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
typedef  scalar_t__ PFNGLSEPARABLEFILTER2DEXTPROC ;
typedef  scalar_t__ PFNGLGETSEPARABLEFILTEREXTPROC ;
typedef  scalar_t__ PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLGETCONVOLUTIONFILTEREXTPROC ;
typedef  scalar_t__ PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC ;
typedef  scalar_t__ PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERIEXTPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERFEXTPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONFILTER2DEXTPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONFILTER1DEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_convolution ; 
 scalar_t__ glad_glConvolutionFilter1DEXT ; 
 scalar_t__ glad_glConvolutionFilter2DEXT ; 
 scalar_t__ glad_glConvolutionParameterfEXT ; 
 scalar_t__ glad_glConvolutionParameterfvEXT ; 
 scalar_t__ glad_glConvolutionParameteriEXT ; 
 scalar_t__ glad_glConvolutionParameterivEXT ; 
 scalar_t__ glad_glCopyConvolutionFilter1DEXT ; 
 scalar_t__ glad_glCopyConvolutionFilter2DEXT ; 
 scalar_t__ glad_glGetConvolutionFilterEXT ; 
 scalar_t__ glad_glGetConvolutionParameterfvEXT ; 
 scalar_t__ glad_glGetConvolutionParameterivEXT ; 
 scalar_t__ glad_glGetSeparableFilterEXT ; 
 scalar_t__ glad_glSeparableFilter2DEXT ; 

__attribute__((used)) static void load_GL_EXT_convolution(GLADloadproc load) {
	if(!GLAD_GL_EXT_convolution) return;
	glad_glConvolutionFilter1DEXT = (PFNGLCONVOLUTIONFILTER1DEXTPROC)load("glConvolutionFilter1DEXT");
	glad_glConvolutionFilter2DEXT = (PFNGLCONVOLUTIONFILTER2DEXTPROC)load("glConvolutionFilter2DEXT");
	glad_glConvolutionParameterfEXT = (PFNGLCONVOLUTIONPARAMETERFEXTPROC)load("glConvolutionParameterfEXT");
	glad_glConvolutionParameterfvEXT = (PFNGLCONVOLUTIONPARAMETERFVEXTPROC)load("glConvolutionParameterfvEXT");
	glad_glConvolutionParameteriEXT = (PFNGLCONVOLUTIONPARAMETERIEXTPROC)load("glConvolutionParameteriEXT");
	glad_glConvolutionParameterivEXT = (PFNGLCONVOLUTIONPARAMETERIVEXTPROC)load("glConvolutionParameterivEXT");
	glad_glCopyConvolutionFilter1DEXT = (PFNGLCOPYCONVOLUTIONFILTER1DEXTPROC)load("glCopyConvolutionFilter1DEXT");
	glad_glCopyConvolutionFilter2DEXT = (PFNGLCOPYCONVOLUTIONFILTER2DEXTPROC)load("glCopyConvolutionFilter2DEXT");
	glad_glGetConvolutionFilterEXT = (PFNGLGETCONVOLUTIONFILTEREXTPROC)load("glGetConvolutionFilterEXT");
	glad_glGetConvolutionParameterfvEXT = (PFNGLGETCONVOLUTIONPARAMETERFVEXTPROC)load("glGetConvolutionParameterfvEXT");
	glad_glGetConvolutionParameterivEXT = (PFNGLGETCONVOLUTIONPARAMETERIVEXTPROC)load("glGetConvolutionParameterivEXT");
	glad_glGetSeparableFilterEXT = (PFNGLGETSEPARABLEFILTEREXTPROC)load("glGetSeparableFilterEXT");
	glad_glSeparableFilter2DEXT = (PFNGLSEPARABLEFILTER2DEXTPROC)load("glSeparableFilter2DEXT");
}