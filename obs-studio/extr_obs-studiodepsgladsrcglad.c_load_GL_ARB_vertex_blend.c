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
typedef  scalar_t__ PFNGLWEIGHTUSVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTUIVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTUBVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTSVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTPOINTERARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTIVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTFVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTDVARBPROC ;
typedef  scalar_t__ PFNGLWEIGHTBVARBPROC ;
typedef  scalar_t__ PFNGLVERTEXBLENDARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_vertex_blend ; 
 scalar_t__ glad_glVertexBlendARB ; 
 scalar_t__ glad_glWeightPointerARB ; 
 scalar_t__ glad_glWeightbvARB ; 
 scalar_t__ glad_glWeightdvARB ; 
 scalar_t__ glad_glWeightfvARB ; 
 scalar_t__ glad_glWeightivARB ; 
 scalar_t__ glad_glWeightsvARB ; 
 scalar_t__ glad_glWeightubvARB ; 
 scalar_t__ glad_glWeightuivARB ; 
 scalar_t__ glad_glWeightusvARB ; 

__attribute__((used)) static void load_GL_ARB_vertex_blend(GLADloadproc load) {
	if(!GLAD_GL_ARB_vertex_blend) return;
	glad_glWeightbvARB = (PFNGLWEIGHTBVARBPROC)load("glWeightbvARB");
	glad_glWeightsvARB = (PFNGLWEIGHTSVARBPROC)load("glWeightsvARB");
	glad_glWeightivARB = (PFNGLWEIGHTIVARBPROC)load("glWeightivARB");
	glad_glWeightfvARB = (PFNGLWEIGHTFVARBPROC)load("glWeightfvARB");
	glad_glWeightdvARB = (PFNGLWEIGHTDVARBPROC)load("glWeightdvARB");
	glad_glWeightubvARB = (PFNGLWEIGHTUBVARBPROC)load("glWeightubvARB");
	glad_glWeightusvARB = (PFNGLWEIGHTUSVARBPROC)load("glWeightusvARB");
	glad_glWeightuivARB = (PFNGLWEIGHTUIVARBPROC)load("glWeightuivARB");
	glad_glWeightPointerARB = (PFNGLWEIGHTPOINTERARBPROC)load("glWeightPointerARB");
	glad_glVertexBlendARB = (PFNGLVERTEXBLENDARBPROC)load("glVertexBlendARB");
}