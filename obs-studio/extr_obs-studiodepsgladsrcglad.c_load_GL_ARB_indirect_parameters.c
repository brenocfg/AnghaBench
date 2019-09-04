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
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_indirect_parameters ; 
 scalar_t__ glad_glMultiDrawArraysIndirectCountARB ; 
 scalar_t__ glad_glMultiDrawElementsIndirectCountARB ; 

__attribute__((used)) static void load_GL_ARB_indirect_parameters(GLADloadproc load) {
	if(!GLAD_GL_ARB_indirect_parameters) return;
	glad_glMultiDrawArraysIndirectCountARB = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC)load("glMultiDrawArraysIndirectCountARB");
	glad_glMultiDrawElementsIndirectCountARB = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC)load("glMultiDrawElementsIndirectCountARB");
}