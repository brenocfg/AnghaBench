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
typedef  scalar_t__ PFNGLUNMAPOBJECTBUFFERATIPROC ;
typedef  scalar_t__ PFNGLMAPOBJECTBUFFERATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_map_object_buffer ; 
 scalar_t__ glad_glMapObjectBufferATI ; 
 scalar_t__ glad_glUnmapObjectBufferATI ; 

__attribute__((used)) static void load_GL_ATI_map_object_buffer(GLADloadproc load) {
	if(!GLAD_GL_ATI_map_object_buffer) return;
	glad_glMapObjectBufferATI = (PFNGLMAPOBJECTBUFFERATIPROC)load("glMapObjectBufferATI");
	glad_glUnmapObjectBufferATI = (PFNGLUNMAPOBJECTBUFFERATIPROC)load("glUnmapObjectBufferATI");
}