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
typedef  scalar_t__ PFNGLUNIFORMSUBROUTINESUIVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4DPROC ;
typedef  scalar_t__ PFNGLUNIFORM3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3DPROC ;
typedef  scalar_t__ PFNGLUNIFORM2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2DPROC ;
typedef  scalar_t__ PFNGLUNIFORM1DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1DPROC ;
typedef  scalar_t__ PFNGLRESUMETRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLPAUSETRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLPATCHPARAMETERIPROC ;
typedef  scalar_t__ PFNGLPATCHPARAMETERFVPROC ;
typedef  scalar_t__ PFNGLMINSAMPLESHADINGPROC ;
typedef  scalar_t__ PFNGLISTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMSUBROUTINEUIVPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMDVPROC ;
typedef  scalar_t__ PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC ;
typedef  scalar_t__ PFNGLGETSUBROUTINEINDEXPROC ;
typedef  scalar_t__ PFNGLGETQUERYINDEXEDIVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMSTAGEIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINENAMEPROC ;
typedef  scalar_t__ PFNGLGENTRANSFORMFEEDBACKSPROC ;
typedef  scalar_t__ PFNGLENDQUERYINDEXEDPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC ;
typedef  scalar_t__ PFNGLDRAWTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINDIRECTPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINDIRECTPROC ;
typedef  scalar_t__ PFNGLDELETETRANSFORMFEEDBACKSPROC ;
typedef  scalar_t__ PFNGLBLENDFUNCSEPARATEIPROC ;
typedef  scalar_t__ PFNGLBLENDFUNCIPROC ;
typedef  scalar_t__ PFNGLBLENDEQUATIONSEPARATEIPROC ;
typedef  scalar_t__ PFNGLBLENDEQUATIONIPROC ;
typedef  scalar_t__ PFNGLBINDTRANSFORMFEEDBACKPROC ;
typedef  scalar_t__ PFNGLBEGINQUERYINDEXEDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_4_0 ; 
 scalar_t__ glad_glBeginQueryIndexed ; 
 scalar_t__ glad_glBindTransformFeedback ; 
 scalar_t__ glad_glBlendEquationSeparatei ; 
 scalar_t__ glad_glBlendEquationi ; 
 scalar_t__ glad_glBlendFuncSeparatei ; 
 scalar_t__ glad_glBlendFunci ; 
 scalar_t__ glad_glDeleteTransformFeedbacks ; 
 scalar_t__ glad_glDrawArraysIndirect ; 
 scalar_t__ glad_glDrawElementsIndirect ; 
 scalar_t__ glad_glDrawTransformFeedback ; 
 scalar_t__ glad_glDrawTransformFeedbackStream ; 
 scalar_t__ glad_glEndQueryIndexed ; 
 scalar_t__ glad_glGenTransformFeedbacks ; 
 scalar_t__ glad_glGetActiveSubroutineName ; 
 scalar_t__ glad_glGetActiveSubroutineUniformName ; 
 scalar_t__ glad_glGetActiveSubroutineUniformiv ; 
 scalar_t__ glad_glGetProgramStageiv ; 
 scalar_t__ glad_glGetQueryIndexediv ; 
 scalar_t__ glad_glGetSubroutineIndex ; 
 scalar_t__ glad_glGetSubroutineUniformLocation ; 
 scalar_t__ glad_glGetUniformSubroutineuiv ; 
 scalar_t__ glad_glGetUniformdv ; 
 scalar_t__ glad_glIsTransformFeedback ; 
 scalar_t__ glad_glMinSampleShading ; 
 scalar_t__ glad_glPatchParameterfv ; 
 scalar_t__ glad_glPatchParameteri ; 
 scalar_t__ glad_glPauseTransformFeedback ; 
 scalar_t__ glad_glResumeTransformFeedback ; 
 scalar_t__ glad_glUniform1d ; 
 scalar_t__ glad_glUniform1dv ; 
 scalar_t__ glad_glUniform2d ; 
 scalar_t__ glad_glUniform2dv ; 
 scalar_t__ glad_glUniform3d ; 
 scalar_t__ glad_glUniform3dv ; 
 scalar_t__ glad_glUniform4d ; 
 scalar_t__ glad_glUniform4dv ; 
 scalar_t__ glad_glUniformMatrix2dv ; 
 scalar_t__ glad_glUniformMatrix2x3dv ; 
 scalar_t__ glad_glUniformMatrix2x4dv ; 
 scalar_t__ glad_glUniformMatrix3dv ; 
 scalar_t__ glad_glUniformMatrix3x2dv ; 
 scalar_t__ glad_glUniformMatrix3x4dv ; 
 scalar_t__ glad_glUniformMatrix4dv ; 
 scalar_t__ glad_glUniformMatrix4x2dv ; 
 scalar_t__ glad_glUniformMatrix4x3dv ; 
 scalar_t__ glad_glUniformSubroutinesuiv ; 

__attribute__((used)) static void load_GL_VERSION_4_0(GLADloadproc load) {
	if(!GLAD_GL_VERSION_4_0) return;
	glad_glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC)load("glMinSampleShading");
	glad_glBlendEquationi = (PFNGLBLENDEQUATIONIPROC)load("glBlendEquationi");
	glad_glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)load("glBlendEquationSeparatei");
	glad_glBlendFunci = (PFNGLBLENDFUNCIPROC)load("glBlendFunci");
	glad_glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC)load("glBlendFuncSeparatei");
	glad_glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)load("glDrawArraysIndirect");
	glad_glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)load("glDrawElementsIndirect");
	glad_glUniform1d = (PFNGLUNIFORM1DPROC)load("glUniform1d");
	glad_glUniform2d = (PFNGLUNIFORM2DPROC)load("glUniform2d");
	glad_glUniform3d = (PFNGLUNIFORM3DPROC)load("glUniform3d");
	glad_glUniform4d = (PFNGLUNIFORM4DPROC)load("glUniform4d");
	glad_glUniform1dv = (PFNGLUNIFORM1DVPROC)load("glUniform1dv");
	glad_glUniform2dv = (PFNGLUNIFORM2DVPROC)load("glUniform2dv");
	glad_glUniform3dv = (PFNGLUNIFORM3DVPROC)load("glUniform3dv");
	glad_glUniform4dv = (PFNGLUNIFORM4DVPROC)load("glUniform4dv");
	glad_glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)load("glUniformMatrix2dv");
	glad_glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)load("glUniformMatrix3dv");
	glad_glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)load("glUniformMatrix4dv");
	glad_glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)load("glUniformMatrix2x3dv");
	glad_glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)load("glUniformMatrix2x4dv");
	glad_glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)load("glUniformMatrix3x2dv");
	glad_glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)load("glUniformMatrix3x4dv");
	glad_glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)load("glUniformMatrix4x2dv");
	glad_glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)load("glUniformMatrix4x3dv");
	glad_glGetUniformdv = (PFNGLGETUNIFORMDVPROC)load("glGetUniformdv");
	glad_glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)load("glGetSubroutineUniformLocation");
	glad_glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)load("glGetSubroutineIndex");
	glad_glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)load("glGetActiveSubroutineUniformiv");
	glad_glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)load("glGetActiveSubroutineUniformName");
	glad_glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)load("glGetActiveSubroutineName");
	glad_glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)load("glUniformSubroutinesuiv");
	glad_glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)load("glGetUniformSubroutineuiv");
	glad_glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)load("glGetProgramStageiv");
	glad_glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)load("glPatchParameteri");
	glad_glPatchParameterfv = (PFNGLPATCHPARAMETERFVPROC)load("glPatchParameterfv");
	glad_glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)load("glBindTransformFeedback");
	glad_glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)load("glDeleteTransformFeedbacks");
	glad_glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)load("glGenTransformFeedbacks");
	glad_glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC)load("glIsTransformFeedback");
	glad_glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)load("glPauseTransformFeedback");
	glad_glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)load("glResumeTransformFeedback");
	glad_glDrawTransformFeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)load("glDrawTransformFeedback");
	glad_glDrawTransformFeedbackStream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)load("glDrawTransformFeedbackStream");
	glad_glBeginQueryIndexed = (PFNGLBEGINQUERYINDEXEDPROC)load("glBeginQueryIndexed");
	glad_glEndQueryIndexed = (PFNGLENDQUERYINDEXEDPROC)load("glEndQueryIndexed");
	glad_glGetQueryIndexediv = (PFNGLGETQUERYINDEXEDIVPROC)load("glGetQueryIndexediv");
}