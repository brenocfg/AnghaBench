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
typedef  scalar_t__ PFNGLISQUERYARBPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTUIVARBPROC ;
typedef  scalar_t__ PFNGLGETQUERYOBJECTIVARBPROC ;
typedef  scalar_t__ PFNGLGETQUERYIVARBPROC ;
typedef  scalar_t__ PFNGLGENQUERIESARBPROC ;
typedef  scalar_t__ PFNGLENDQUERYARBPROC ;
typedef  scalar_t__ PFNGLDELETEQUERIESARBPROC ;
typedef  scalar_t__ PFNGLBEGINQUERYARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_occlusion_query ; 
 scalar_t__ glad_glBeginQueryARB ; 
 scalar_t__ glad_glDeleteQueriesARB ; 
 scalar_t__ glad_glEndQueryARB ; 
 scalar_t__ glad_glGenQueriesARB ; 
 scalar_t__ glad_glGetQueryObjectivARB ; 
 scalar_t__ glad_glGetQueryObjectuivARB ; 
 scalar_t__ glad_glGetQueryivARB ; 
 scalar_t__ glad_glIsQueryARB ; 

__attribute__((used)) static void load_GL_ARB_occlusion_query(GLADloadproc load) {
	if(!GLAD_GL_ARB_occlusion_query) return;
	glad_glGenQueriesARB = (PFNGLGENQUERIESARBPROC)load("glGenQueriesARB");
	glad_glDeleteQueriesARB = (PFNGLDELETEQUERIESARBPROC)load("glDeleteQueriesARB");
	glad_glIsQueryARB = (PFNGLISQUERYARBPROC)load("glIsQueryARB");
	glad_glBeginQueryARB = (PFNGLBEGINQUERYARBPROC)load("glBeginQueryARB");
	glad_glEndQueryARB = (PFNGLENDQUERYARBPROC)load("glEndQueryARB");
	glad_glGetQueryivARB = (PFNGLGETQUERYIVARBPROC)load("glGetQueryivARB");
	glad_glGetQueryObjectivARB = (PFNGLGETQUERYOBJECTIVARBPROC)load("glGetQueryObjectivARB");
	glad_glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC)load("glGetQueryObjectuivARB");
}