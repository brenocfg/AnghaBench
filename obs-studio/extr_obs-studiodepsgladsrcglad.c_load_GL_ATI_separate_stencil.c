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
typedef  scalar_t__ PFNGLSTENCILOPSEPARATEATIPROC ;
typedef  scalar_t__ PFNGLSTENCILFUNCSEPARATEATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_separate_stencil ; 
 scalar_t__ glad_glStencilFuncSeparateATI ; 
 scalar_t__ glad_glStencilOpSeparateATI ; 

__attribute__((used)) static void load_GL_ATI_separate_stencil(GLADloadproc load) {
	if(!GLAD_GL_ATI_separate_stencil) return;
	glad_glStencilOpSeparateATI = (PFNGLSTENCILOPSEPARATEATIPROC)load("glStencilOpSeparateATI");
	glad_glStencilFuncSeparateATI = (PFNGLSTENCILFUNCSEPARATEATIPROC)load("glStencilFuncSeparateATI");
}