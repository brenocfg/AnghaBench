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
typedef  scalar_t__ PFNGLVERTEXARRAYRANGENVPROC ;
typedef  scalar_t__ PFNGLFLUSHVERTEXARRAYRANGENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_vertex_array_range ; 
 scalar_t__ glad_glFlushVertexArrayRangeNV ; 
 scalar_t__ glad_glVertexArrayRangeNV ; 

__attribute__((used)) static void load_GL_NV_vertex_array_range(GLADloadproc load) {
	if(!GLAD_GL_NV_vertex_array_range) return;
	glad_glFlushVertexArrayRangeNV = (PFNGLFLUSHVERTEXARRAYRANGENVPROC)load("glFlushVertexArrayRangeNV");
	glad_glVertexArrayRangeNV = (PFNGLVERTEXARRAYRANGENVPROC)load("glVertexArrayRangeNV");
}