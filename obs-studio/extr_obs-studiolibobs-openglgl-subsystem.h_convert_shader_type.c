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
typedef  enum gs_shader_type { ____Placeholder_gs_shader_type } gs_shader_type ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
#define  GS_SHADER_PIXEL 129 
#define  GS_SHADER_VERTEX 128 

__attribute__((used)) static inline GLenum convert_shader_type(enum gs_shader_type type)
{
	switch (type) {
	case GS_SHADER_VERTEX: return GL_VERTEX_SHADER;
	case GS_SHADER_PIXEL:  return GL_FRAGMENT_SHADER;
	}

	return GL_VERTEX_SHADER;
}