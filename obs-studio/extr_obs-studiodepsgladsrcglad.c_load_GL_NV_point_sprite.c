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
typedef  scalar_t__ PFNGLPOINTPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERINVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_point_sprite ; 
 scalar_t__ glad_glPointParameteriNV ; 
 scalar_t__ glad_glPointParameterivNV ; 

__attribute__((used)) static void load_GL_NV_point_sprite(GLADloadproc load) {
	if(!GLAD_GL_NV_point_sprite) return;
	glad_glPointParameteriNV = (PFNGLPOINTPARAMETERINVPROC)load("glPointParameteriNV");
	glad_glPointParameterivNV = (PFNGLPOINTPARAMETERIVNVPROC)load("glPointParameterivNV");
}