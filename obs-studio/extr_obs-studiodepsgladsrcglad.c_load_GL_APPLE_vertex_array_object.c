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
typedef  scalar_t__ PFNGLISVERTEXARRAYAPPLEPROC ;
typedef  scalar_t__ PFNGLGENVERTEXARRAYSAPPLEPROC ;
typedef  scalar_t__ PFNGLDELETEVERTEXARRAYSAPPLEPROC ;
typedef  scalar_t__ PFNGLBINDVERTEXARRAYAPPLEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_APPLE_vertex_array_object ; 
 scalar_t__ glad_glBindVertexArrayAPPLE ; 
 scalar_t__ glad_glDeleteVertexArraysAPPLE ; 
 scalar_t__ glad_glGenVertexArraysAPPLE ; 
 scalar_t__ glad_glIsVertexArrayAPPLE ; 

__attribute__((used)) static void load_GL_APPLE_vertex_array_object(GLADloadproc load) {
	if(!GLAD_GL_APPLE_vertex_array_object) return;
	glad_glBindVertexArrayAPPLE = (PFNGLBINDVERTEXARRAYAPPLEPROC)load("glBindVertexArrayAPPLE");
	glad_glDeleteVertexArraysAPPLE = (PFNGLDELETEVERTEXARRAYSAPPLEPROC)load("glDeleteVertexArraysAPPLE");
	glad_glGenVertexArraysAPPLE = (PFNGLGENVERTEXARRAYSAPPLEPROC)load("glGenVertexArraysAPPLE");
	glad_glIsVertexArrayAPPLE = (PFNGLISVERTEXARRAYAPPLEPROC)load("glIsVertexArrayAPPLE");
}