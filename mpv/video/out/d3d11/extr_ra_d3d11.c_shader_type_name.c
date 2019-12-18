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
typedef  enum glsl_shader { ____Placeholder_glsl_shader } glsl_shader ;

/* Variables and functions */
#define  GLSL_SHADER_COMPUTE 130 
#define  GLSL_SHADER_FRAGMENT 129 
#define  GLSL_SHADER_VERTEX 128 

__attribute__((used)) static const char *shader_type_name(enum glsl_shader type)
{
    switch (type) {
    case GLSL_SHADER_VERTEX:   return "vertex";
    case GLSL_SHADER_FRAGMENT: return "fragment";
    case GLSL_SHADER_COMPUTE:  return "compute";
    default:                   return "unknown";
    }
}