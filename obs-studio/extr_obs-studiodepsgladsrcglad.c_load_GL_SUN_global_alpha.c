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
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORUSSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORUISUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORUBSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORSSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORISUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORFSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORDSUNPROC ;
typedef  scalar_t__ PFNGLGLOBALALPHAFACTORBSUNPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SUN_global_alpha ; 
 scalar_t__ glad_glGlobalAlphaFactorbSUN ; 
 scalar_t__ glad_glGlobalAlphaFactordSUN ; 
 scalar_t__ glad_glGlobalAlphaFactorfSUN ; 
 scalar_t__ glad_glGlobalAlphaFactoriSUN ; 
 scalar_t__ glad_glGlobalAlphaFactorsSUN ; 
 scalar_t__ glad_glGlobalAlphaFactorubSUN ; 
 scalar_t__ glad_glGlobalAlphaFactoruiSUN ; 
 scalar_t__ glad_glGlobalAlphaFactorusSUN ; 

__attribute__((used)) static void load_GL_SUN_global_alpha(GLADloadproc load) {
	if(!GLAD_GL_SUN_global_alpha) return;
	glad_glGlobalAlphaFactorbSUN = (PFNGLGLOBALALPHAFACTORBSUNPROC)load("glGlobalAlphaFactorbSUN");
	glad_glGlobalAlphaFactorsSUN = (PFNGLGLOBALALPHAFACTORSSUNPROC)load("glGlobalAlphaFactorsSUN");
	glad_glGlobalAlphaFactoriSUN = (PFNGLGLOBALALPHAFACTORISUNPROC)load("glGlobalAlphaFactoriSUN");
	glad_glGlobalAlphaFactorfSUN = (PFNGLGLOBALALPHAFACTORFSUNPROC)load("glGlobalAlphaFactorfSUN");
	glad_glGlobalAlphaFactordSUN = (PFNGLGLOBALALPHAFACTORDSUNPROC)load("glGlobalAlphaFactordSUN");
	glad_glGlobalAlphaFactorubSUN = (PFNGLGLOBALALPHAFACTORUBSUNPROC)load("glGlobalAlphaFactorubSUN");
	glad_glGlobalAlphaFactorusSUN = (PFNGLGLOBALALPHAFACTORUSSUNPROC)load("glGlobalAlphaFactorusSUN");
	glad_glGlobalAlphaFactoruiSUN = (PFNGLGLOBALALPHAFACTORUISUNPROC)load("glGlobalAlphaFactoruiSUN");
}