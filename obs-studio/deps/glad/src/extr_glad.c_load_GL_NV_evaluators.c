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
typedef  scalar_t__ PFNGLMAPPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLMAPPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLMAPCONTROLPOINTSNVPROC ;
typedef  scalar_t__ PFNGLGETMAPPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLGETMAPPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLGETMAPCONTROLPOINTSNVPROC ;
typedef  scalar_t__ PFNGLGETMAPATTRIBPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLGETMAPATTRIBPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLEVALMAPSNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_evaluators ; 
 scalar_t__ glad_glEvalMapsNV ; 
 scalar_t__ glad_glGetMapAttribParameterfvNV ; 
 scalar_t__ glad_glGetMapAttribParameterivNV ; 
 scalar_t__ glad_glGetMapControlPointsNV ; 
 scalar_t__ glad_glGetMapParameterfvNV ; 
 scalar_t__ glad_glGetMapParameterivNV ; 
 scalar_t__ glad_glMapControlPointsNV ; 
 scalar_t__ glad_glMapParameterfvNV ; 
 scalar_t__ glad_glMapParameterivNV ; 

__attribute__((used)) static void load_GL_NV_evaluators(GLADloadproc load) {
	if(!GLAD_GL_NV_evaluators) return;
	glad_glMapControlPointsNV = (PFNGLMAPCONTROLPOINTSNVPROC)load("glMapControlPointsNV");
	glad_glMapParameterivNV = (PFNGLMAPPARAMETERIVNVPROC)load("glMapParameterivNV");
	glad_glMapParameterfvNV = (PFNGLMAPPARAMETERFVNVPROC)load("glMapParameterfvNV");
	glad_glGetMapControlPointsNV = (PFNGLGETMAPCONTROLPOINTSNVPROC)load("glGetMapControlPointsNV");
	glad_glGetMapParameterivNV = (PFNGLGETMAPPARAMETERIVNVPROC)load("glGetMapParameterivNV");
	glad_glGetMapParameterfvNV = (PFNGLGETMAPPARAMETERFVNVPROC)load("glGetMapParameterfvNV");
	glad_glGetMapAttribParameterivNV = (PFNGLGETMAPATTRIBPARAMETERIVNVPROC)load("glGetMapAttribParameterivNV");
	glad_glGetMapAttribParameterfvNV = (PFNGLGETMAPATTRIBPARAMETERFVNVPROC)load("glGetMapAttribParameterfvNV");
	glad_glEvalMapsNV = (PFNGLEVALMAPSNVPROC)load("glEvalMapsNV");
}