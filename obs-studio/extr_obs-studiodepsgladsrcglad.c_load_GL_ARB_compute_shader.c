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
typedef  scalar_t__ PFNGLDISPATCHCOMPUTEPROC ;
typedef  scalar_t__ PFNGLDISPATCHCOMPUTEINDIRECTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_compute_shader ; 
 scalar_t__ glad_glDispatchCompute ; 
 scalar_t__ glad_glDispatchComputeIndirect ; 

__attribute__((used)) static void load_GL_ARB_compute_shader(GLADloadproc load) {
	if(!GLAD_GL_ARB_compute_shader) return;
	glad_glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)load("glDispatchCompute");
	glad_glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)load("glDispatchComputeIndirect");
}