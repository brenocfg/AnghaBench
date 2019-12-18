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
typedef  scalar_t__ PFNGLXQUERYRENDERERSTRINGMESAPROC ;
typedef  scalar_t__ PFNGLXQUERYRENDERERINTEGERMESAPROC ;
typedef  scalar_t__ PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC ;
typedef  scalar_t__ PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_MESA_query_renderer ; 
 scalar_t__ glad_glXQueryCurrentRendererIntegerMESA ; 
 scalar_t__ glad_glXQueryCurrentRendererStringMESA ; 
 scalar_t__ glad_glXQueryRendererIntegerMESA ; 
 scalar_t__ glad_glXQueryRendererStringMESA ; 

__attribute__((used)) static void load_GLX_MESA_query_renderer(GLADloadproc load) {
	if(!GLAD_GLX_MESA_query_renderer) return;
	glad_glXQueryCurrentRendererIntegerMESA = (PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC)load("glXQueryCurrentRendererIntegerMESA");
	glad_glXQueryCurrentRendererStringMESA = (PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC)load("glXQueryCurrentRendererStringMESA");
	glad_glXQueryRendererIntegerMESA = (PFNGLXQUERYRENDERERINTEGERMESAPROC)load("glXQueryRendererIntegerMESA");
	glad_glXQueryRendererStringMESA = (PFNGLXQUERYRENDERERSTRINGMESAPROC)load("glXQueryRendererStringMESA");
}