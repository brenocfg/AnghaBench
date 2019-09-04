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
typedef  scalar_t__ PFNGLFRAMETERMINATORGREMEDYPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_GREMEDY_frame_terminator ; 
 scalar_t__ glad_glFrameTerminatorGREMEDY ; 

__attribute__((used)) static void load_GL_GREMEDY_frame_terminator(GLADloadproc load) {
	if(!GLAD_GL_GREMEDY_frame_terminator) return;
	glad_glFrameTerminatorGREMEDY = (PFNGLFRAMETERMINATORGREMEDYPROC)load("glFrameTerminatorGREMEDY");
}