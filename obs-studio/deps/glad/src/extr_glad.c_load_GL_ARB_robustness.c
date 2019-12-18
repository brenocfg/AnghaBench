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
typedef  scalar_t__ PFNGLREADNPIXELSARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMUIVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMIVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMFVARBPROC ;
typedef  scalar_t__ PFNGLGETNUNIFORMDVARBPROC ;
typedef  scalar_t__ PFNGLGETNTEXIMAGEARBPROC ;
typedef  scalar_t__ PFNGLGETNSEPARABLEFILTERARBPROC ;
typedef  scalar_t__ PFNGLGETNPOLYGONSTIPPLEARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPUSVARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPUIVARBPROC ;
typedef  scalar_t__ PFNGLGETNPIXELMAPFVARBPROC ;
typedef  scalar_t__ PFNGLGETNMINMAXARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPIVARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPFVARBPROC ;
typedef  scalar_t__ PFNGLGETNMAPDVARBPROC ;
typedef  scalar_t__ PFNGLGETNHISTOGRAMARBPROC ;
typedef  scalar_t__ PFNGLGETNCONVOLUTIONFILTERARBPROC ;
typedef  scalar_t__ PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC ;
typedef  scalar_t__ PFNGLGETNCOLORTABLEARBPROC ;
typedef  scalar_t__ PFNGLGETGRAPHICSRESETSTATUSARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_robustness ; 
 scalar_t__ glad_glGetGraphicsResetStatusARB ; 
 scalar_t__ glad_glGetnColorTableARB ; 
 scalar_t__ glad_glGetnCompressedTexImageARB ; 
 scalar_t__ glad_glGetnConvolutionFilterARB ; 
 scalar_t__ glad_glGetnHistogramARB ; 
 scalar_t__ glad_glGetnMapdvARB ; 
 scalar_t__ glad_glGetnMapfvARB ; 
 scalar_t__ glad_glGetnMapivARB ; 
 scalar_t__ glad_glGetnMinmaxARB ; 
 scalar_t__ glad_glGetnPixelMapfvARB ; 
 scalar_t__ glad_glGetnPixelMapuivARB ; 
 scalar_t__ glad_glGetnPixelMapusvARB ; 
 scalar_t__ glad_glGetnPolygonStippleARB ; 
 scalar_t__ glad_glGetnSeparableFilterARB ; 
 scalar_t__ glad_glGetnTexImageARB ; 
 scalar_t__ glad_glGetnUniformdvARB ; 
 scalar_t__ glad_glGetnUniformfvARB ; 
 scalar_t__ glad_glGetnUniformivARB ; 
 scalar_t__ glad_glGetnUniformuivARB ; 
 scalar_t__ glad_glReadnPixelsARB ; 

__attribute__((used)) static void load_GL_ARB_robustness(GLADloadproc load) {
	if(!GLAD_GL_ARB_robustness) return;
	glad_glGetGraphicsResetStatusARB = (PFNGLGETGRAPHICSRESETSTATUSARBPROC)load("glGetGraphicsResetStatusARB");
	glad_glGetnTexImageARB = (PFNGLGETNTEXIMAGEARBPROC)load("glGetnTexImageARB");
	glad_glReadnPixelsARB = (PFNGLREADNPIXELSARBPROC)load("glReadnPixelsARB");
	glad_glGetnCompressedTexImageARB = (PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC)load("glGetnCompressedTexImageARB");
	glad_glGetnUniformfvARB = (PFNGLGETNUNIFORMFVARBPROC)load("glGetnUniformfvARB");
	glad_glGetnUniformivARB = (PFNGLGETNUNIFORMIVARBPROC)load("glGetnUniformivARB");
	glad_glGetnUniformuivARB = (PFNGLGETNUNIFORMUIVARBPROC)load("glGetnUniformuivARB");
	glad_glGetnUniformdvARB = (PFNGLGETNUNIFORMDVARBPROC)load("glGetnUniformdvARB");
	glad_glGetnMapdvARB = (PFNGLGETNMAPDVARBPROC)load("glGetnMapdvARB");
	glad_glGetnMapfvARB = (PFNGLGETNMAPFVARBPROC)load("glGetnMapfvARB");
	glad_glGetnMapivARB = (PFNGLGETNMAPIVARBPROC)load("glGetnMapivARB");
	glad_glGetnPixelMapfvARB = (PFNGLGETNPIXELMAPFVARBPROC)load("glGetnPixelMapfvARB");
	glad_glGetnPixelMapuivARB = (PFNGLGETNPIXELMAPUIVARBPROC)load("glGetnPixelMapuivARB");
	glad_glGetnPixelMapusvARB = (PFNGLGETNPIXELMAPUSVARBPROC)load("glGetnPixelMapusvARB");
	glad_glGetnPolygonStippleARB = (PFNGLGETNPOLYGONSTIPPLEARBPROC)load("glGetnPolygonStippleARB");
	glad_glGetnColorTableARB = (PFNGLGETNCOLORTABLEARBPROC)load("glGetnColorTableARB");
	glad_glGetnConvolutionFilterARB = (PFNGLGETNCONVOLUTIONFILTERARBPROC)load("glGetnConvolutionFilterARB");
	glad_glGetnSeparableFilterARB = (PFNGLGETNSEPARABLEFILTERARBPROC)load("glGetnSeparableFilterARB");
	glad_glGetnHistogramARB = (PFNGLGETNHISTOGRAMARBPROC)load("glGetnHistogramARB");
	glad_glGetnMinmaxARB = (PFNGLGETNMINMAXARBPROC)load("glGetnMinmaxARB");
}