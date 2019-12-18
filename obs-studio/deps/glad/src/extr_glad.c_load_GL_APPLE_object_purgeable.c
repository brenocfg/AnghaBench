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
typedef  scalar_t__ PFNGLOBJECTUNPURGEABLEAPPLEPROC ;
typedef  scalar_t__ PFNGLOBJECTPURGEABLEAPPLEPROC ;
typedef  scalar_t__ PFNGLGETOBJECTPARAMETERIVAPPLEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_APPLE_object_purgeable ; 
 scalar_t__ glad_glGetObjectParameterivAPPLE ; 
 scalar_t__ glad_glObjectPurgeableAPPLE ; 
 scalar_t__ glad_glObjectUnpurgeableAPPLE ; 

__attribute__((used)) static void load_GL_APPLE_object_purgeable(GLADloadproc load) {
	if(!GLAD_GL_APPLE_object_purgeable) return;
	glad_glObjectPurgeableAPPLE = (PFNGLOBJECTPURGEABLEAPPLEPROC)load("glObjectPurgeableAPPLE");
	glad_glObjectUnpurgeableAPPLE = (PFNGLOBJECTUNPURGEABLEAPPLEPROC)load("glObjectUnpurgeableAPPLE");
	glad_glGetObjectParameterivAPPLE = (PFNGLGETOBJECTPARAMETERIVAPPLEPROC)load("glGetObjectParameterivAPPLE");
}