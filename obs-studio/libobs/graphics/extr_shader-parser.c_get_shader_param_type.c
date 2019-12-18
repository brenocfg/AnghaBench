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
typedef  enum gs_shader_param_type { ____Placeholder_gs_shader_param_type } gs_shader_param_type ;

/* Variables and functions */
 int GS_SHADER_PARAM_BOOL ; 
 int GS_SHADER_PARAM_FLOAT ; 
 int GS_SHADER_PARAM_INT ; 
 int GS_SHADER_PARAM_INT2 ; 
 int GS_SHADER_PARAM_INT3 ; 
 int GS_SHADER_PARAM_INT4 ; 
 int GS_SHADER_PARAM_MATRIX4X4 ; 
 int GS_SHADER_PARAM_STRING ; 
 int GS_SHADER_PARAM_TEXTURE ; 
 int GS_SHADER_PARAM_UNKNOWN ; 
 int GS_SHADER_PARAM_VEC2 ; 
 int GS_SHADER_PARAM_VEC3 ; 
 int GS_SHADER_PARAM_VEC4 ; 
 scalar_t__ astrcmp_n (char const*,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

enum gs_shader_param_type get_shader_param_type(const char *type)
{
	if (strcmp(type, "float") == 0)
		return GS_SHADER_PARAM_FLOAT;
	else if (strcmp(type, "float2") == 0)
		return GS_SHADER_PARAM_VEC2;
	else if (strcmp(type, "float3") == 0)
		return GS_SHADER_PARAM_VEC3;
	else if (strcmp(type, "float4") == 0)
		return GS_SHADER_PARAM_VEC4;
	else if (strcmp(type, "int2") == 0)
		return GS_SHADER_PARAM_INT2;
	else if (strcmp(type, "int3") == 0)
		return GS_SHADER_PARAM_INT3;
	else if (strcmp(type, "int4") == 0)
		return GS_SHADER_PARAM_INT4;
	else if (astrcmp_n(type, "texture", 7) == 0)
		return GS_SHADER_PARAM_TEXTURE;
	else if (strcmp(type, "float4x4") == 0)
		return GS_SHADER_PARAM_MATRIX4X4;
	else if (strcmp(type, "bool") == 0)
		return GS_SHADER_PARAM_BOOL;
	else if (strcmp(type, "int") == 0)
		return GS_SHADER_PARAM_INT;
	else if (strcmp(type, "string") == 0)
		return GS_SHADER_PARAM_STRING;

	return GS_SHADER_PARAM_UNKNOWN;
}