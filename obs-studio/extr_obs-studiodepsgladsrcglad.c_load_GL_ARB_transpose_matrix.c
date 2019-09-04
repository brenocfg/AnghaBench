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
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXFARBPROC ;
typedef  scalar_t__ PFNGLMULTTRANSPOSEMATRIXDARBPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXFARBPROC ;
typedef  scalar_t__ PFNGLLOADTRANSPOSEMATRIXDARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_transpose_matrix ; 
 scalar_t__ glad_glLoadTransposeMatrixdARB ; 
 scalar_t__ glad_glLoadTransposeMatrixfARB ; 
 scalar_t__ glad_glMultTransposeMatrixdARB ; 
 scalar_t__ glad_glMultTransposeMatrixfARB ; 

__attribute__((used)) static void load_GL_ARB_transpose_matrix(GLADloadproc load) {
	if(!GLAD_GL_ARB_transpose_matrix) return;
	glad_glLoadTransposeMatrixfARB = (PFNGLLOADTRANSPOSEMATRIXFARBPROC)load("glLoadTransposeMatrixfARB");
	glad_glLoadTransposeMatrixdARB = (PFNGLLOADTRANSPOSEMATRIXDARBPROC)load("glLoadTransposeMatrixdARB");
	glad_glMultTransposeMatrixfARB = (PFNGLMULTTRANSPOSEMATRIXFARBPROC)load("glMultTransposeMatrixfARB");
	glad_glMultTransposeMatrixdARB = (PFNGLMULTTRANSPOSEMATRIXDARBPROC)load("glMultTransposeMatrixdARB");
}