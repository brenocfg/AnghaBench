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
typedef  scalar_t__ PFNGLFOGCOORDPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLFOGCOORDFVEXTPROC ;
typedef  scalar_t__ PFNGLFOGCOORDFEXTPROC ;
typedef  scalar_t__ PFNGLFOGCOORDDVEXTPROC ;
typedef  scalar_t__ PFNGLFOGCOORDDEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_fog_coord ; 
 scalar_t__ glad_glFogCoordPointerEXT ; 
 scalar_t__ glad_glFogCoorddEXT ; 
 scalar_t__ glad_glFogCoorddvEXT ; 
 scalar_t__ glad_glFogCoordfEXT ; 
 scalar_t__ glad_glFogCoordfvEXT ; 

__attribute__((used)) static void load_GL_EXT_fog_coord(GLADloadproc load) {
	if(!GLAD_GL_EXT_fog_coord) return;
	glad_glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC)load("glFogCoordfEXT");
	glad_glFogCoordfvEXT = (PFNGLFOGCOORDFVEXTPROC)load("glFogCoordfvEXT");
	glad_glFogCoorddEXT = (PFNGLFOGCOORDDEXTPROC)load("glFogCoorddEXT");
	glad_glFogCoorddvEXT = (PFNGLFOGCOORDDVEXTPROC)load("glFogCoorddvEXT");
	glad_glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC)load("glFogCoordPointerEXT");
}