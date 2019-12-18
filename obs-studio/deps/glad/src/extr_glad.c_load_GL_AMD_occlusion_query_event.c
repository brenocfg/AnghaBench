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
typedef  scalar_t__ PFNGLQUERYOBJECTPARAMETERUIAMDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_AMD_occlusion_query_event ; 
 scalar_t__ glad_glQueryObjectParameteruiAMD ; 

__attribute__((used)) static void load_GL_AMD_occlusion_query_event(GLADloadproc load) {
	if(!GLAD_GL_AMD_occlusion_query_event) return;
	glad_glQueryObjectParameteruiAMD = (PFNGLQUERYOBJECTPARAMETERUIAMDPROC)load("glQueryObjectParameteruiAMD");
}