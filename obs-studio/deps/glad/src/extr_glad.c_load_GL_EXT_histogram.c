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
typedef  scalar_t__ PFNGLRESETMINMAXEXTPROC ;
typedef  scalar_t__ PFNGLRESETHISTOGRAMEXTPROC ;
typedef  scalar_t__ PFNGLMINMAXEXTPROC ;
typedef  scalar_t__ PFNGLHISTOGRAMEXTPROC ;
typedef  scalar_t__ PFNGLGETMINMAXPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETMINMAXPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLGETMINMAXEXTPROC ;
typedef  scalar_t__ PFNGLGETHISTOGRAMPARAMETERIVEXTPROC ;
typedef  scalar_t__ PFNGLGETHISTOGRAMPARAMETERFVEXTPROC ;
typedef  scalar_t__ PFNGLGETHISTOGRAMEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_histogram ; 
 scalar_t__ glad_glGetHistogramEXT ; 
 scalar_t__ glad_glGetHistogramParameterfvEXT ; 
 scalar_t__ glad_glGetHistogramParameterivEXT ; 
 scalar_t__ glad_glGetMinmaxEXT ; 
 scalar_t__ glad_glGetMinmaxParameterfvEXT ; 
 scalar_t__ glad_glGetMinmaxParameterivEXT ; 
 scalar_t__ glad_glHistogramEXT ; 
 scalar_t__ glad_glMinmaxEXT ; 
 scalar_t__ glad_glResetHistogramEXT ; 
 scalar_t__ glad_glResetMinmaxEXT ; 

__attribute__((used)) static void load_GL_EXT_histogram(GLADloadproc load) {
	if(!GLAD_GL_EXT_histogram) return;
	glad_glGetHistogramEXT = (PFNGLGETHISTOGRAMEXTPROC)load("glGetHistogramEXT");
	glad_glGetHistogramParameterfvEXT = (PFNGLGETHISTOGRAMPARAMETERFVEXTPROC)load("glGetHistogramParameterfvEXT");
	glad_glGetHistogramParameterivEXT = (PFNGLGETHISTOGRAMPARAMETERIVEXTPROC)load("glGetHistogramParameterivEXT");
	glad_glGetMinmaxEXT = (PFNGLGETMINMAXEXTPROC)load("glGetMinmaxEXT");
	glad_glGetMinmaxParameterfvEXT = (PFNGLGETMINMAXPARAMETERFVEXTPROC)load("glGetMinmaxParameterfvEXT");
	glad_glGetMinmaxParameterivEXT = (PFNGLGETMINMAXPARAMETERIVEXTPROC)load("glGetMinmaxParameterivEXT");
	glad_glHistogramEXT = (PFNGLHISTOGRAMEXTPROC)load("glHistogramEXT");
	glad_glMinmaxEXT = (PFNGLMINMAXEXTPROC)load("glMinmaxEXT");
	glad_glResetHistogramEXT = (PFNGLRESETHISTOGRAMEXTPROC)load("glResetHistogramEXT");
	glad_glResetMinmaxEXT = (PFNGLRESETMINMAXEXTPROC)load("glResetMinmaxEXT");
}