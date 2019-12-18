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
typedef  scalar_t__ PFNGLLIGHTENVISGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTMATERIALIVSGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTMATERIALFVSGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTLIGHTIVSGIXPROC ;
typedef  scalar_t__ PFNGLGETFRAGMENTLIGHTFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALIVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALISGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTMATERIALFSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELIVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELISGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTMODELFSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTIVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTISGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTFVSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTLIGHTFSGIXPROC ;
typedef  scalar_t__ PFNGLFRAGMENTCOLORMATERIALSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIX_fragment_lighting ; 
 scalar_t__ glad_glFragmentColorMaterialSGIX ; 
 scalar_t__ glad_glFragmentLightModelfSGIX ; 
 scalar_t__ glad_glFragmentLightModelfvSGIX ; 
 scalar_t__ glad_glFragmentLightModeliSGIX ; 
 scalar_t__ glad_glFragmentLightModelivSGIX ; 
 scalar_t__ glad_glFragmentLightfSGIX ; 
 scalar_t__ glad_glFragmentLightfvSGIX ; 
 scalar_t__ glad_glFragmentLightiSGIX ; 
 scalar_t__ glad_glFragmentLightivSGIX ; 
 scalar_t__ glad_glFragmentMaterialfSGIX ; 
 scalar_t__ glad_glFragmentMaterialfvSGIX ; 
 scalar_t__ glad_glFragmentMaterialiSGIX ; 
 scalar_t__ glad_glFragmentMaterialivSGIX ; 
 scalar_t__ glad_glGetFragmentLightfvSGIX ; 
 scalar_t__ glad_glGetFragmentLightivSGIX ; 
 scalar_t__ glad_glGetFragmentMaterialfvSGIX ; 
 scalar_t__ glad_glGetFragmentMaterialivSGIX ; 
 scalar_t__ glad_glLightEnviSGIX ; 

__attribute__((used)) static void load_GL_SGIX_fragment_lighting(GLADloadproc load) {
	if(!GLAD_GL_SGIX_fragment_lighting) return;
	glad_glFragmentColorMaterialSGIX = (PFNGLFRAGMENTCOLORMATERIALSGIXPROC)load("glFragmentColorMaterialSGIX");
	glad_glFragmentLightfSGIX = (PFNGLFRAGMENTLIGHTFSGIXPROC)load("glFragmentLightfSGIX");
	glad_glFragmentLightfvSGIX = (PFNGLFRAGMENTLIGHTFVSGIXPROC)load("glFragmentLightfvSGIX");
	glad_glFragmentLightiSGIX = (PFNGLFRAGMENTLIGHTISGIXPROC)load("glFragmentLightiSGIX");
	glad_glFragmentLightivSGIX = (PFNGLFRAGMENTLIGHTIVSGIXPROC)load("glFragmentLightivSGIX");
	glad_glFragmentLightModelfSGIX = (PFNGLFRAGMENTLIGHTMODELFSGIXPROC)load("glFragmentLightModelfSGIX");
	glad_glFragmentLightModelfvSGIX = (PFNGLFRAGMENTLIGHTMODELFVSGIXPROC)load("glFragmentLightModelfvSGIX");
	glad_glFragmentLightModeliSGIX = (PFNGLFRAGMENTLIGHTMODELISGIXPROC)load("glFragmentLightModeliSGIX");
	glad_glFragmentLightModelivSGIX = (PFNGLFRAGMENTLIGHTMODELIVSGIXPROC)load("glFragmentLightModelivSGIX");
	glad_glFragmentMaterialfSGIX = (PFNGLFRAGMENTMATERIALFSGIXPROC)load("glFragmentMaterialfSGIX");
	glad_glFragmentMaterialfvSGIX = (PFNGLFRAGMENTMATERIALFVSGIXPROC)load("glFragmentMaterialfvSGIX");
	glad_glFragmentMaterialiSGIX = (PFNGLFRAGMENTMATERIALISGIXPROC)load("glFragmentMaterialiSGIX");
	glad_glFragmentMaterialivSGIX = (PFNGLFRAGMENTMATERIALIVSGIXPROC)load("glFragmentMaterialivSGIX");
	glad_glGetFragmentLightfvSGIX = (PFNGLGETFRAGMENTLIGHTFVSGIXPROC)load("glGetFragmentLightfvSGIX");
	glad_glGetFragmentLightivSGIX = (PFNGLGETFRAGMENTLIGHTIVSGIXPROC)load("glGetFragmentLightivSGIX");
	glad_glGetFragmentMaterialfvSGIX = (PFNGLGETFRAGMENTMATERIALFVSGIXPROC)load("glGetFragmentMaterialfvSGIX");
	glad_glGetFragmentMaterialivSGIX = (PFNGLGETFRAGMENTMATERIALIVSGIXPROC)load("glGetFragmentMaterialivSGIX");
	glad_glLightEnviSGIX = (PFNGLLIGHTENVISGIXPROC)load("glLightEnviSGIX");
}