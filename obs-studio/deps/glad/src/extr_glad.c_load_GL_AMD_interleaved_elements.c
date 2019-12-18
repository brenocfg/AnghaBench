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
typedef  scalar_t__ PFNGLVERTEXATTRIBPARAMETERIAMDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_AMD_interleaved_elements ; 
 scalar_t__ glad_glVertexAttribParameteriAMD ; 

__attribute__((used)) static void load_GL_AMD_interleaved_elements(GLADloadproc load) {
	if(!GLAD_GL_AMD_interleaved_elements) return;
	glad_glVertexAttribParameteriAMD = (PFNGLVERTEXATTRIBPARAMETERIAMDPROC)load("glVertexAttribParameteriAMD");
}