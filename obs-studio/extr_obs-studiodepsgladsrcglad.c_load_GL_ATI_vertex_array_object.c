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
typedef  scalar_t__ PFNGLVARIANTARRAYOBJECTATIPROC ;
typedef  scalar_t__ PFNGLUPDATEOBJECTBUFFERATIPROC ;
typedef  scalar_t__ PFNGLNEWOBJECTBUFFERATIPROC ;
typedef  scalar_t__ PFNGLISOBJECTBUFFERATIPROC ;
typedef  scalar_t__ PFNGLGETVARIANTARRAYOBJECTIVATIPROC ;
typedef  scalar_t__ PFNGLGETVARIANTARRAYOBJECTFVATIPROC ;
typedef  scalar_t__ PFNGLGETOBJECTBUFFERIVATIPROC ;
typedef  scalar_t__ PFNGLGETOBJECTBUFFERFVATIPROC ;
typedef  scalar_t__ PFNGLGETARRAYOBJECTIVATIPROC ;
typedef  scalar_t__ PFNGLGETARRAYOBJECTFVATIPROC ;
typedef  scalar_t__ PFNGLFREEOBJECTBUFFERATIPROC ;
typedef  scalar_t__ PFNGLARRAYOBJECTATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_vertex_array_object ; 
 scalar_t__ glad_glArrayObjectATI ; 
 scalar_t__ glad_glFreeObjectBufferATI ; 
 scalar_t__ glad_glGetArrayObjectfvATI ; 
 scalar_t__ glad_glGetArrayObjectivATI ; 
 scalar_t__ glad_glGetObjectBufferfvATI ; 
 scalar_t__ glad_glGetObjectBufferivATI ; 
 scalar_t__ glad_glGetVariantArrayObjectfvATI ; 
 scalar_t__ glad_glGetVariantArrayObjectivATI ; 
 scalar_t__ glad_glIsObjectBufferATI ; 
 scalar_t__ glad_glNewObjectBufferATI ; 
 scalar_t__ glad_glUpdateObjectBufferATI ; 
 scalar_t__ glad_glVariantArrayObjectATI ; 

__attribute__((used)) static void load_GL_ATI_vertex_array_object(GLADloadproc load) {
	if(!GLAD_GL_ATI_vertex_array_object) return;
	glad_glNewObjectBufferATI = (PFNGLNEWOBJECTBUFFERATIPROC)load("glNewObjectBufferATI");
	glad_glIsObjectBufferATI = (PFNGLISOBJECTBUFFERATIPROC)load("glIsObjectBufferATI");
	glad_glUpdateObjectBufferATI = (PFNGLUPDATEOBJECTBUFFERATIPROC)load("glUpdateObjectBufferATI");
	glad_glGetObjectBufferfvATI = (PFNGLGETOBJECTBUFFERFVATIPROC)load("glGetObjectBufferfvATI");
	glad_glGetObjectBufferivATI = (PFNGLGETOBJECTBUFFERIVATIPROC)load("glGetObjectBufferivATI");
	glad_glFreeObjectBufferATI = (PFNGLFREEOBJECTBUFFERATIPROC)load("glFreeObjectBufferATI");
	glad_glArrayObjectATI = (PFNGLARRAYOBJECTATIPROC)load("glArrayObjectATI");
	glad_glGetArrayObjectfvATI = (PFNGLGETARRAYOBJECTFVATIPROC)load("glGetArrayObjectfvATI");
	glad_glGetArrayObjectivATI = (PFNGLGETARRAYOBJECTIVATIPROC)load("glGetArrayObjectivATI");
	glad_glVariantArrayObjectATI = (PFNGLVARIANTARRAYOBJECTATIPROC)load("glVariantArrayObjectATI");
	glad_glGetVariantArrayObjectfvATI = (PFNGLGETVARIANTARRAYOBJECTFVATIPROC)load("glGetVariantArrayObjectfvATI");
	glad_glGetVariantArrayObjectivATI = (PFNGLGETVARIANTARRAYOBJECTIVATIPROC)load("glGetVariantArrayObjectivATI");
}