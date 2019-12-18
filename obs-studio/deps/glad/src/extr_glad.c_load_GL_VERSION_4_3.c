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
typedef  scalar_t__ PFNGLVERTEXBINDINGDIVISORPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBLFORMATPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBIFORMATPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBFORMATPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBBINDINGPROC ;
typedef  scalar_t__ PFNGLTEXTUREVIEWPROC ;
typedef  scalar_t__ PFNGLTEXSTORAGE3DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXSTORAGE2DMULTISAMPLEPROC ;
typedef  scalar_t__ PFNGLTEXBUFFERRANGEPROC ;
typedef  scalar_t__ PFNGLSHADERSTORAGEBLOCKBINDINGPROC ;
typedef  scalar_t__ PFNGLPUSHDEBUGGROUPPROC ;
typedef  scalar_t__ PFNGLPOPDEBUGGROUPPROC ;
typedef  scalar_t__ PFNGLOBJECTPTRLABELPROC ;
typedef  scalar_t__ PFNGLOBJECTLABELPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSINDIRECTPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWARRAYSINDIRECTPROC ;
typedef  scalar_t__ PFNGLINVALIDATETEXSUBIMAGEPROC ;
typedef  scalar_t__ PFNGLINVALIDATETEXIMAGEPROC ;
typedef  scalar_t__ PFNGLINVALIDATESUBFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLINVALIDATEFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLINVALIDATEBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLINVALIDATEBUFFERDATAPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMRESOURCENAMEPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMRESOURCELOCATIONPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMRESOURCEIVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMRESOURCEINDEXPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMINTERFACEIVPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPTRLABELPROC ;
typedef  scalar_t__ PFNGLGETOBJECTLABELPROC ;
typedef  scalar_t__ PFNGLGETINTERNALFORMATI64VPROC ;
typedef  scalar_t__ PFNGLGETFRAMEBUFFERPARAMETERIVPROC ;
typedef  scalar_t__ PFNGLGETDEBUGMESSAGELOGPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERPARAMETERIPROC ;
typedef  scalar_t__ PFNGLDISPATCHCOMPUTEPROC ;
typedef  scalar_t__ PFNGLDISPATCHCOMPUTEINDIRECTPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGEINSERTPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECONTROLPROC ;
typedef  scalar_t__ PFNGLDEBUGMESSAGECALLBACKPROC ;
typedef  scalar_t__ PFNGLCOPYIMAGESUBDATAPROC ;
typedef  scalar_t__ PFNGLCLEARBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLCLEARBUFFERDATAPROC ;
typedef  scalar_t__ PFNGLBINDVERTEXBUFFERPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_4_3 ; 
 scalar_t__ glad_glBindVertexBuffer ; 
 scalar_t__ glad_glClearBufferData ; 
 scalar_t__ glad_glClearBufferSubData ; 
 scalar_t__ glad_glCopyImageSubData ; 
 scalar_t__ glad_glDebugMessageCallback ; 
 scalar_t__ glad_glDebugMessageControl ; 
 scalar_t__ glad_glDebugMessageInsert ; 
 scalar_t__ glad_glDispatchCompute ; 
 scalar_t__ glad_glDispatchComputeIndirect ; 
 scalar_t__ glad_glFramebufferParameteri ; 
 scalar_t__ glad_glGetDebugMessageLog ; 
 scalar_t__ glad_glGetFramebufferParameteriv ; 
 scalar_t__ glad_glGetInternalformati64v ; 
 scalar_t__ glad_glGetObjectLabel ; 
 scalar_t__ glad_glGetObjectPtrLabel ; 
 scalar_t__ glad_glGetProgramInterfaceiv ; 
 scalar_t__ glad_glGetProgramResourceIndex ; 
 scalar_t__ glad_glGetProgramResourceLocation ; 
 scalar_t__ glad_glGetProgramResourceLocationIndex ; 
 scalar_t__ glad_glGetProgramResourceName ; 
 scalar_t__ glad_glGetProgramResourceiv ; 
 scalar_t__ glad_glInvalidateBufferData ; 
 scalar_t__ glad_glInvalidateBufferSubData ; 
 scalar_t__ glad_glInvalidateFramebuffer ; 
 scalar_t__ glad_glInvalidateSubFramebuffer ; 
 scalar_t__ glad_glInvalidateTexImage ; 
 scalar_t__ glad_glInvalidateTexSubImage ; 
 scalar_t__ glad_glMultiDrawArraysIndirect ; 
 scalar_t__ glad_glMultiDrawElementsIndirect ; 
 scalar_t__ glad_glObjectLabel ; 
 scalar_t__ glad_glObjectPtrLabel ; 
 scalar_t__ glad_glPopDebugGroup ; 
 scalar_t__ glad_glPushDebugGroup ; 
 scalar_t__ glad_glShaderStorageBlockBinding ; 
 scalar_t__ glad_glTexBufferRange ; 
 scalar_t__ glad_glTexStorage2DMultisample ; 
 scalar_t__ glad_glTexStorage3DMultisample ; 
 scalar_t__ glad_glTextureView ; 
 scalar_t__ glad_glVertexAttribBinding ; 
 scalar_t__ glad_glVertexAttribFormat ; 
 scalar_t__ glad_glVertexAttribIFormat ; 
 scalar_t__ glad_glVertexAttribLFormat ; 
 scalar_t__ glad_glVertexBindingDivisor ; 

__attribute__((used)) static void load_GL_VERSION_4_3(GLADloadproc load) {
	if(!GLAD_GL_VERSION_4_3) return;
	glad_glClearBufferData = (PFNGLCLEARBUFFERDATAPROC)load("glClearBufferData");
	glad_glClearBufferSubData = (PFNGLCLEARBUFFERSUBDATAPROC)load("glClearBufferSubData");
	glad_glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)load("glDispatchCompute");
	glad_glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)load("glDispatchComputeIndirect");
	glad_glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC)load("glCopyImageSubData");
	glad_glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)load("glFramebufferParameteri");
	glad_glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)load("glGetFramebufferParameteriv");
	glad_glGetInternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)load("glGetInternalformati64v");
	glad_glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)load("glInvalidateTexSubImage");
	glad_glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)load("glInvalidateTexImage");
	glad_glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)load("glInvalidateBufferSubData");
	glad_glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)load("glInvalidateBufferData");
	glad_glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)load("glInvalidateFramebuffer");
	glad_glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)load("glInvalidateSubFramebuffer");
	glad_glMultiDrawArraysIndirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)load("glMultiDrawArraysIndirect");
	glad_glMultiDrawElementsIndirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)load("glMultiDrawElementsIndirect");
	glad_glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)load("glGetProgramInterfaceiv");
	glad_glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)load("glGetProgramResourceIndex");
	glad_glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC)load("glGetProgramResourceName");
	glad_glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)load("glGetProgramResourceiv");
	glad_glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)load("glGetProgramResourceLocation");
	glad_glGetProgramResourceLocationIndex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)load("glGetProgramResourceLocationIndex");
	glad_glShaderStorageBlockBinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)load("glShaderStorageBlockBinding");
	glad_glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC)load("glTexBufferRange");
	glad_glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)load("glTexStorage2DMultisample");
	glad_glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)load("glTexStorage3DMultisample");
	glad_glTextureView = (PFNGLTEXTUREVIEWPROC)load("glTextureView");
	glad_glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC)load("glBindVertexBuffer");
	glad_glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC)load("glVertexAttribFormat");
	glad_glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC)load("glVertexAttribIFormat");
	glad_glVertexAttribLFormat = (PFNGLVERTEXATTRIBLFORMATPROC)load("glVertexAttribLFormat");
	glad_glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC)load("glVertexAttribBinding");
	glad_glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC)load("glVertexBindingDivisor");
	glad_glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)load("glDebugMessageControl");
	glad_glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)load("glDebugMessageInsert");
	glad_glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)load("glDebugMessageCallback");
	glad_glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC)load("glGetDebugMessageLog");
	glad_glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC)load("glPushDebugGroup");
	glad_glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC)load("glPopDebugGroup");
	glad_glObjectLabel = (PFNGLOBJECTLABELPROC)load("glObjectLabel");
	glad_glGetObjectLabel = (PFNGLGETOBJECTLABELPROC)load("glGetObjectLabel");
	glad_glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC)load("glObjectPtrLabel");
	glad_glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC)load("glGetObjectPtrLabel");
}