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
typedef  scalar_t__ PFNGLMULTIMODEDRAWELEMENTSIBMPROC ;
typedef  scalar_t__ PFNGLMULTIMODEDRAWARRAYSIBMPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_IBM_multimode_draw_arrays ; 
 scalar_t__ glad_glMultiModeDrawArraysIBM ; 
 scalar_t__ glad_glMultiModeDrawElementsIBM ; 

__attribute__((used)) static void load_GL_IBM_multimode_draw_arrays(GLADloadproc load) {
	if(!GLAD_GL_IBM_multimode_draw_arrays) return;
	glad_glMultiModeDrawArraysIBM = (PFNGLMULTIMODEDRAWARRAYSIBMPROC)load("glMultiModeDrawArraysIBM");
	glad_glMultiModeDrawElementsIBM = (PFNGLMULTIMODEDRAWELEMENTSIBMPROC)load("glMultiModeDrawElementsIBM");
}