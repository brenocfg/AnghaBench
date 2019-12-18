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
typedef  scalar_t__ PFNGLINVALIDATETEXSUBIMAGEPROC ;
typedef  scalar_t__ PFNGLINVALIDATETEXIMAGEPROC ;
typedef  scalar_t__ PFNGLINVALIDATESUBFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLINVALIDATEFRAMEBUFFERPROC ;
typedef  scalar_t__ PFNGLINVALIDATEBUFFERSUBDATAPROC ;
typedef  scalar_t__ PFNGLINVALIDATEBUFFERDATAPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_invalidate_subdata ; 
 scalar_t__ glad_glInvalidateBufferData ; 
 scalar_t__ glad_glInvalidateBufferSubData ; 
 scalar_t__ glad_glInvalidateFramebuffer ; 
 scalar_t__ glad_glInvalidateSubFramebuffer ; 
 scalar_t__ glad_glInvalidateTexImage ; 
 scalar_t__ glad_glInvalidateTexSubImage ; 

__attribute__((used)) static void load_GL_ARB_invalidate_subdata(GLADloadproc load) {
	if(!GLAD_GL_ARB_invalidate_subdata) return;
	glad_glInvalidateTexSubImage = (PFNGLINVALIDATETEXSUBIMAGEPROC)load("glInvalidateTexSubImage");
	glad_glInvalidateTexImage = (PFNGLINVALIDATETEXIMAGEPROC)load("glInvalidateTexImage");
	glad_glInvalidateBufferSubData = (PFNGLINVALIDATEBUFFERSUBDATAPROC)load("glInvalidateBufferSubData");
	glad_glInvalidateBufferData = (PFNGLINVALIDATEBUFFERDATAPROC)load("glInvalidateBufferData");
	glad_glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)load("glInvalidateFramebuffer");
	glad_glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)load("glInvalidateSubFramebuffer");
}