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
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_base_instance ; 
 scalar_t__ glad_glDrawArraysInstancedBaseInstance ; 
 scalar_t__ glad_glDrawElementsInstancedBaseInstance ; 
 scalar_t__ glad_glDrawElementsInstancedBaseVertexBaseInstance ; 

__attribute__((used)) static void load_GL_ARB_base_instance(GLADloadproc load) {
	if(!GLAD_GL_ARB_base_instance) return;
	glad_glDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)load("glDrawArraysInstancedBaseInstance");
	glad_glDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)load("glDrawElementsInstancedBaseInstance");
	glad_glDrawElementsInstancedBaseVertexBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)load("glDrawElementsInstancedBaseVertexBaseInstance");
}