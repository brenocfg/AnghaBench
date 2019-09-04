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
typedef  enum gs_stencil_side { ____Placeholder_gs_stencil_side } gs_stencil_side ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
#define  GS_STENCIL_BACK 130 
#define  GS_STENCIL_BOTH 129 
#define  GS_STENCIL_FRONT 128 

__attribute__((used)) static inline GLenum convert_gs_stencil_side(enum gs_stencil_side side)
{
	switch (side) {
	case GS_STENCIL_FRONT: return GL_FRONT;
	case GS_STENCIL_BACK:  return GL_BACK;
	case GS_STENCIL_BOTH:  return GL_FRONT_AND_BACK;
	}

	return GL_FRONT;
}