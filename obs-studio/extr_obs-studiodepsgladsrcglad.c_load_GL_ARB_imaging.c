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
typedef  scalar_t__ PFNGLSEPARABLEFILTER2DPROC ;
typedef  scalar_t__ PFNGLRESETMINMAXPROC ;
typedef  scalar_t__ PFNGLRESETHISTOGRAMPROC ;
typedef  scalar_t__ PFNGLMINMAXPROC ;
typedef  scalar_t__ PFNGLHISTOGRAMPROC ;
typedef  scalar_t__ PFNGLGETSEPARABLEFILTERPROC ;
typedef  scalar_t__ PFNGLGETMINMAXPROC ;
typedef  scalar_t__ PFNGLGETMINMAXPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETMINMAXPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLGETHISTOGRAMPROC ;
typedef  scalar_t__ PFNGLGETHISTOGRAMPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETHISTOGRAMPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLGETCONVOLUTIONPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETCONVOLUTIONPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLGETCONVOLUTIONFILTERPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETCOLORTABLEPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLCOPYCONVOLUTIONFILTER2DPROC ;
typedef  scalar_t__ PFNGLCOPYCONVOLUTIONFILTER1DPROC ;
typedef  scalar_t__ PFNGLCOPYCOLORTABLEPROC ;
typedef  scalar_t__ PFNGLCOPYCOLORSUBTABLEPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERIPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONPARAMETERFPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONFILTER2DPROC ;
typedef  scalar_t__ PFNGLCONVOLUTIONFILTER1DPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLCOLORTABLEPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLCOLORSUBTABLEPROC ;
typedef  scalar_t__ PFNGLBLENDEQUATIONPROC ;
typedef  scalar_t__ PFNGLBLENDCOLORPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_imaging ; 
 scalar_t__ glad_glBlendColor ; 
 scalar_t__ glad_glBlendEquation ; 
 scalar_t__ glad_glColorSubTable ; 
 scalar_t__ glad_glColorTable ; 
 scalar_t__ glad_glColorTableParameterfv ; 
 scalar_t__ glad_glColorTableParameteriv ; 
 scalar_t__ glad_glConvolutionFilter1D ; 
 scalar_t__ glad_glConvolutionFilter2D ; 
 scalar_t__ glad_glConvolutionParameterf ; 
 scalar_t__ glad_glConvolutionParameterfv ; 
 scalar_t__ glad_glConvolutionParameteri ; 
 scalar_t__ glad_glConvolutionParameteriv ; 
 scalar_t__ glad_glCopyColorSubTable ; 
 scalar_t__ glad_glCopyColorTable ; 
 scalar_t__ glad_glCopyConvolutionFilter1D ; 
 scalar_t__ glad_glCopyConvolutionFilter2D ; 
 scalar_t__ glad_glGetColorTable ; 
 scalar_t__ glad_glGetColorTableParameterfv ; 
 scalar_t__ glad_glGetColorTableParameteriv ; 
 scalar_t__ glad_glGetConvolutionFilter ; 
 scalar_t__ glad_glGetConvolutionParameterfv ; 
 scalar_t__ glad_glGetConvolutionParameteriv ; 
 scalar_t__ glad_glGetHistogram ; 
 scalar_t__ glad_glGetHistogramParameterfv ; 
 scalar_t__ glad_glGetHistogramParameteriv ; 
 scalar_t__ glad_glGetMinmax ; 
 scalar_t__ glad_glGetMinmaxParameterfv ; 
 scalar_t__ glad_glGetMinmaxParameteriv ; 
 scalar_t__ glad_glGetSeparableFilter ; 
 scalar_t__ glad_glHistogram ; 
 scalar_t__ glad_glMinmax ; 
 scalar_t__ glad_glResetHistogram ; 
 scalar_t__ glad_glResetMinmax ; 
 scalar_t__ glad_glSeparableFilter2D ; 

__attribute__((used)) static void load_GL_ARB_imaging(GLADloadproc load) {
	if(!GLAD_GL_ARB_imaging) return;
	glad_glBlendColor = (PFNGLBLENDCOLORPROC)load("glBlendColor");
	glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC)load("glBlendEquation");
	glad_glColorTable = (PFNGLCOLORTABLEPROC)load("glColorTable");
	glad_glColorTableParameterfv = (PFNGLCOLORTABLEPARAMETERFVPROC)load("glColorTableParameterfv");
	glad_glColorTableParameteriv = (PFNGLCOLORTABLEPARAMETERIVPROC)load("glColorTableParameteriv");
	glad_glCopyColorTable = (PFNGLCOPYCOLORTABLEPROC)load("glCopyColorTable");
	glad_glGetColorTable = (PFNGLGETCOLORTABLEPROC)load("glGetColorTable");
	glad_glGetColorTableParameterfv = (PFNGLGETCOLORTABLEPARAMETERFVPROC)load("glGetColorTableParameterfv");
	glad_glGetColorTableParameteriv = (PFNGLGETCOLORTABLEPARAMETERIVPROC)load("glGetColorTableParameteriv");
	glad_glColorSubTable = (PFNGLCOLORSUBTABLEPROC)load("glColorSubTable");
	glad_glCopyColorSubTable = (PFNGLCOPYCOLORSUBTABLEPROC)load("glCopyColorSubTable");
	glad_glConvolutionFilter1D = (PFNGLCONVOLUTIONFILTER1DPROC)load("glConvolutionFilter1D");
	glad_glConvolutionFilter2D = (PFNGLCONVOLUTIONFILTER2DPROC)load("glConvolutionFilter2D");
	glad_glConvolutionParameterf = (PFNGLCONVOLUTIONPARAMETERFPROC)load("glConvolutionParameterf");
	glad_glConvolutionParameterfv = (PFNGLCONVOLUTIONPARAMETERFVPROC)load("glConvolutionParameterfv");
	glad_glConvolutionParameteri = (PFNGLCONVOLUTIONPARAMETERIPROC)load("glConvolutionParameteri");
	glad_glConvolutionParameteriv = (PFNGLCONVOLUTIONPARAMETERIVPROC)load("glConvolutionParameteriv");
	glad_glCopyConvolutionFilter1D = (PFNGLCOPYCONVOLUTIONFILTER1DPROC)load("glCopyConvolutionFilter1D");
	glad_glCopyConvolutionFilter2D = (PFNGLCOPYCONVOLUTIONFILTER2DPROC)load("glCopyConvolutionFilter2D");
	glad_glGetConvolutionFilter = (PFNGLGETCONVOLUTIONFILTERPROC)load("glGetConvolutionFilter");
	glad_glGetConvolutionParameterfv = (PFNGLGETCONVOLUTIONPARAMETERFVPROC)load("glGetConvolutionParameterfv");
	glad_glGetConvolutionParameteriv = (PFNGLGETCONVOLUTIONPARAMETERIVPROC)load("glGetConvolutionParameteriv");
	glad_glGetSeparableFilter = (PFNGLGETSEPARABLEFILTERPROC)load("glGetSeparableFilter");
	glad_glSeparableFilter2D = (PFNGLSEPARABLEFILTER2DPROC)load("glSeparableFilter2D");
	glad_glGetHistogram = (PFNGLGETHISTOGRAMPROC)load("glGetHistogram");
	glad_glGetHistogramParameterfv = (PFNGLGETHISTOGRAMPARAMETERFVPROC)load("glGetHistogramParameterfv");
	glad_glGetHistogramParameteriv = (PFNGLGETHISTOGRAMPARAMETERIVPROC)load("glGetHistogramParameteriv");
	glad_glGetMinmax = (PFNGLGETMINMAXPROC)load("glGetMinmax");
	glad_glGetMinmaxParameterfv = (PFNGLGETMINMAXPARAMETERFVPROC)load("glGetMinmaxParameterfv");
	glad_glGetMinmaxParameteriv = (PFNGLGETMINMAXPARAMETERIVPROC)load("glGetMinmaxParameteriv");
	glad_glHistogram = (PFNGLHISTOGRAMPROC)load("glHistogram");
	glad_glMinmax = (PFNGLMINMAXPROC)load("glMinmax");
	glad_glResetHistogram = (PFNGLRESETHISTOGRAMPROC)load("glResetHistogram");
	glad_glResetMinmax = (PFNGLRESETMINMAXPROC)load("glResetMinmax");
}