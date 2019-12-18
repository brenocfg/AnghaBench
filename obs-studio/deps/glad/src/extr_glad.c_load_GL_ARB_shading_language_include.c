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
typedef  scalar_t__ PFNGLNAMEDSTRINGARBPROC ;
typedef  scalar_t__ PFNGLISNAMEDSTRINGARBPROC ;
typedef  scalar_t__ PFNGLGETNAMEDSTRINGIVARBPROC ;
typedef  scalar_t__ PFNGLGETNAMEDSTRINGARBPROC ;
typedef  scalar_t__ PFNGLDELETENAMEDSTRINGARBPROC ;
typedef  scalar_t__ PFNGLCOMPILESHADERINCLUDEARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_shading_language_include ; 
 scalar_t__ glad_glCompileShaderIncludeARB ; 
 scalar_t__ glad_glDeleteNamedStringARB ; 
 scalar_t__ glad_glGetNamedStringARB ; 
 scalar_t__ glad_glGetNamedStringivARB ; 
 scalar_t__ glad_glIsNamedStringARB ; 
 scalar_t__ glad_glNamedStringARB ; 

__attribute__((used)) static void load_GL_ARB_shading_language_include(GLADloadproc load) {
	if(!GLAD_GL_ARB_shading_language_include) return;
	glad_glNamedStringARB = (PFNGLNAMEDSTRINGARBPROC)load("glNamedStringARB");
	glad_glDeleteNamedStringARB = (PFNGLDELETENAMEDSTRINGARBPROC)load("glDeleteNamedStringARB");
	glad_glCompileShaderIncludeARB = (PFNGLCOMPILESHADERINCLUDEARBPROC)load("glCompileShaderIncludeARB");
	glad_glIsNamedStringARB = (PFNGLISNAMEDSTRINGARBPROC)load("glIsNamedStringARB");
	glad_glGetNamedStringARB = (PFNGLGETNAMEDSTRINGARBPROC)load("glGetNamedStringARB");
	glad_glGetNamedStringivARB = (PFNGLGETNAMEDSTRINGIVARBPROC)load("glGetNamedStringivARB");
}