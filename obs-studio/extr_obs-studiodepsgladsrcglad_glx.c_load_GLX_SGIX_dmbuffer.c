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
typedef  int /*<<< orphan*/  GLADloadproc ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGIX_dmbuffer ; 

__attribute__((used)) static void load_GLX_SGIX_dmbuffer(GLADloadproc load) {
	if(!GLAD_GLX_SGIX_dmbuffer) return;
#ifdef _DM_BUFFER_H_
	glad_glXAssociateDMPbufferSGIX = (PFNGLXASSOCIATEDMPBUFFERSGIXPROC)load("glXAssociateDMPbufferSGIX");
#else
	(void)load;
#endif
}