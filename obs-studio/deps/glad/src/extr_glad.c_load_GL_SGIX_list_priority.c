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
typedef  scalar_t__ PFNGLLISTPARAMETERIVSGIXPROC ;
typedef  scalar_t__ PFNGLLISTPARAMETERISGIXPROC ;
typedef  scalar_t__ PFNGLLISTPARAMETERFVSGIXPROC ;
typedef  scalar_t__ PFNGLLISTPARAMETERFSGIXPROC ;
typedef  scalar_t__ PFNGLGETLISTPARAMETERIVSGIXPROC ;
typedef  scalar_t__ PFNGLGETLISTPARAMETERFVSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIX_list_priority ; 
 scalar_t__ glad_glGetListParameterfvSGIX ; 
 scalar_t__ glad_glGetListParameterivSGIX ; 
 scalar_t__ glad_glListParameterfSGIX ; 
 scalar_t__ glad_glListParameterfvSGIX ; 
 scalar_t__ glad_glListParameteriSGIX ; 
 scalar_t__ glad_glListParameterivSGIX ; 

__attribute__((used)) static void load_GL_SGIX_list_priority(GLADloadproc load) {
	if(!GLAD_GL_SGIX_list_priority) return;
	glad_glGetListParameterfvSGIX = (PFNGLGETLISTPARAMETERFVSGIXPROC)load("glGetListParameterfvSGIX");
	glad_glGetListParameterivSGIX = (PFNGLGETLISTPARAMETERIVSGIXPROC)load("glGetListParameterivSGIX");
	glad_glListParameterfSGIX = (PFNGLLISTPARAMETERFSGIXPROC)load("glListParameterfSGIX");
	glad_glListParameterfvSGIX = (PFNGLLISTPARAMETERFVSGIXPROC)load("glListParameterfvSGIX");
	glad_glListParameteriSGIX = (PFNGLLISTPARAMETERISGIXPROC)load("glListParameteriSGIX");
	glad_glListParameterivSGIX = (PFNGLLISTPARAMETERIVSGIXPROC)load("glListParameterivSGIX");
}