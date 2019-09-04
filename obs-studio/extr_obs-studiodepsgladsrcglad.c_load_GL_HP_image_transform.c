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
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERIVHPPROC ;
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERIHPPROC ;
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERFVHPPROC ;
typedef  scalar_t__ PFNGLIMAGETRANSFORMPARAMETERFHPPROC ;
typedef  scalar_t__ PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC ;
typedef  scalar_t__ PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_HP_image_transform ; 
 scalar_t__ glad_glGetImageTransformParameterfvHP ; 
 scalar_t__ glad_glGetImageTransformParameterivHP ; 
 scalar_t__ glad_glImageTransformParameterfHP ; 
 scalar_t__ glad_glImageTransformParameterfvHP ; 
 scalar_t__ glad_glImageTransformParameteriHP ; 
 scalar_t__ glad_glImageTransformParameterivHP ; 

__attribute__((used)) static void load_GL_HP_image_transform(GLADloadproc load) {
	if(!GLAD_GL_HP_image_transform) return;
	glad_glImageTransformParameteriHP = (PFNGLIMAGETRANSFORMPARAMETERIHPPROC)load("glImageTransformParameteriHP");
	glad_glImageTransformParameterfHP = (PFNGLIMAGETRANSFORMPARAMETERFHPPROC)load("glImageTransformParameterfHP");
	glad_glImageTransformParameterivHP = (PFNGLIMAGETRANSFORMPARAMETERIVHPPROC)load("glImageTransformParameterivHP");
	glad_glImageTransformParameterfvHP = (PFNGLIMAGETRANSFORMPARAMETERFVHPPROC)load("glImageTransformParameterfvHP");
	glad_glGetImageTransformParameterivHP = (PFNGLGETIMAGETRANSFORMPARAMETERIVHPPROC)load("glGetImageTransformParameterivHP");
	glad_glGetImageTransformParameterfvHP = (PFNGLGETIMAGETRANSFORMPARAMETERFVHPPROC)load("glGetImageTransformParameterfvHP");
}