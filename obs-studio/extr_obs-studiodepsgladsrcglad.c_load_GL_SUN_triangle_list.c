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
typedef  scalar_t__ PFNGLREPLACEMENTCODEUSVSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUSSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUIVSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUISUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUBVSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEUBSUNPROC ;
typedef  scalar_t__ PFNGLREPLACEMENTCODEPOINTERSUNPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SUN_triangle_list ; 
 scalar_t__ glad_glReplacementCodePointerSUN ; 
 scalar_t__ glad_glReplacementCodeubSUN ; 
 scalar_t__ glad_glReplacementCodeubvSUN ; 
 scalar_t__ glad_glReplacementCodeuiSUN ; 
 scalar_t__ glad_glReplacementCodeuivSUN ; 
 scalar_t__ glad_glReplacementCodeusSUN ; 
 scalar_t__ glad_glReplacementCodeusvSUN ; 

__attribute__((used)) static void load_GL_SUN_triangle_list(GLADloadproc load) {
	if(!GLAD_GL_SUN_triangle_list) return;
	glad_glReplacementCodeuiSUN = (PFNGLREPLACEMENTCODEUISUNPROC)load("glReplacementCodeuiSUN");
	glad_glReplacementCodeusSUN = (PFNGLREPLACEMENTCODEUSSUNPROC)load("glReplacementCodeusSUN");
	glad_glReplacementCodeubSUN = (PFNGLREPLACEMENTCODEUBSUNPROC)load("glReplacementCodeubSUN");
	glad_glReplacementCodeuivSUN = (PFNGLREPLACEMENTCODEUIVSUNPROC)load("glReplacementCodeuivSUN");
	glad_glReplacementCodeusvSUN = (PFNGLREPLACEMENTCODEUSVSUNPROC)load("glReplacementCodeusvSUN");
	glad_glReplacementCodeubvSUN = (PFNGLREPLACEMENTCODEUBVSUNPROC)load("glReplacementCodeubvSUN");
	glad_glReplacementCodePointerSUN = (PFNGLREPLACEMENTCODEPOINTERSUNPROC)load("glReplacementCodePointerSUN");
}