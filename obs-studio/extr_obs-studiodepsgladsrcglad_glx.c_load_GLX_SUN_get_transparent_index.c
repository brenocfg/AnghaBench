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
typedef  scalar_t__ PFNGLXGETTRANSPARENTINDEXSUNPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SUN_get_transparent_index ; 
 scalar_t__ glad_glXGetTransparentIndexSUN ; 

__attribute__((used)) static void load_GLX_SUN_get_transparent_index(GLADloadproc load) {
	if(!GLAD_GLX_SUN_get_transparent_index) return;
	glad_glXGetTransparentIndexSUN = (PFNGLXGETTRANSPARENTINDEXSUNPROC)load("glXGetTransparentIndexSUN");
}