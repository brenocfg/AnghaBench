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
typedef  scalar_t__ PFNGLPOINTPARAMETERFVARBPROC ;
typedef  scalar_t__ PFNGLPOINTPARAMETERFARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_point_parameters ; 
 scalar_t__ glad_glPointParameterfARB ; 
 scalar_t__ glad_glPointParameterfvARB ; 

__attribute__((used)) static void load_GL_ARB_point_parameters(GLADloadproc load) {
	if(!GLAD_GL_ARB_point_parameters) return;
	glad_glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC)load("glPointParameterfARB");
	glad_glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC)load("glPointParameterfvARB");
}