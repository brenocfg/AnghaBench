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
typedef  scalar_t__ PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLFINALCOMBINERINPUTNVPROC ;
typedef  scalar_t__ PFNGLCOMBINERPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLCOMBINERPARAMETERINVPROC ;
typedef  scalar_t__ PFNGLCOMBINERPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLCOMBINERPARAMETERFNVPROC ;
typedef  scalar_t__ PFNGLCOMBINEROUTPUTNVPROC ;
typedef  scalar_t__ PFNGLCOMBINERINPUTNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_register_combiners ; 
 scalar_t__ glad_glCombinerInputNV ; 
 scalar_t__ glad_glCombinerOutputNV ; 
 scalar_t__ glad_glCombinerParameterfNV ; 
 scalar_t__ glad_glCombinerParameterfvNV ; 
 scalar_t__ glad_glCombinerParameteriNV ; 
 scalar_t__ glad_glCombinerParameterivNV ; 
 scalar_t__ glad_glFinalCombinerInputNV ; 
 scalar_t__ glad_glGetCombinerInputParameterfvNV ; 
 scalar_t__ glad_glGetCombinerInputParameterivNV ; 
 scalar_t__ glad_glGetCombinerOutputParameterfvNV ; 
 scalar_t__ glad_glGetCombinerOutputParameterivNV ; 
 scalar_t__ glad_glGetFinalCombinerInputParameterfvNV ; 
 scalar_t__ glad_glGetFinalCombinerInputParameterivNV ; 

__attribute__((used)) static void load_GL_NV_register_combiners(GLADloadproc load) {
	if(!GLAD_GL_NV_register_combiners) return;
	glad_glCombinerParameterfvNV = (PFNGLCOMBINERPARAMETERFVNVPROC)load("glCombinerParameterfvNV");
	glad_glCombinerParameterfNV = (PFNGLCOMBINERPARAMETERFNVPROC)load("glCombinerParameterfNV");
	glad_glCombinerParameterivNV = (PFNGLCOMBINERPARAMETERIVNVPROC)load("glCombinerParameterivNV");
	glad_glCombinerParameteriNV = (PFNGLCOMBINERPARAMETERINVPROC)load("glCombinerParameteriNV");
	glad_glCombinerInputNV = (PFNGLCOMBINERINPUTNVPROC)load("glCombinerInputNV");
	glad_glCombinerOutputNV = (PFNGLCOMBINEROUTPUTNVPROC)load("glCombinerOutputNV");
	glad_glFinalCombinerInputNV = (PFNGLFINALCOMBINERINPUTNVPROC)load("glFinalCombinerInputNV");
	glad_glGetCombinerInputParameterfvNV = (PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC)load("glGetCombinerInputParameterfvNV");
	glad_glGetCombinerInputParameterivNV = (PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC)load("glGetCombinerInputParameterivNV");
	glad_glGetCombinerOutputParameterfvNV = (PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC)load("glGetCombinerOutputParameterfvNV");
	glad_glGetCombinerOutputParameterivNV = (PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC)load("glGetCombinerOutputParameterivNV");
	glad_glGetFinalCombinerInputParameterfvNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC)load("glGetFinalCombinerInputParameterfvNV");
	glad_glGetFinalCombinerInputParameterivNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC)load("glGetFinalCombinerInputParameterivNV");
}