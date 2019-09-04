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
typedef  int arm_vectordata_type ;

/* Variables and functions */
#define  ARM_VECTORDATA_F16F32 164 
#define  ARM_VECTORDATA_F16F64 163 
#define  ARM_VECTORDATA_F32 162 
#define  ARM_VECTORDATA_F32F16 161 
#define  ARM_VECTORDATA_F32F64 160 
#define  ARM_VECTORDATA_F32S16 159 
#define  ARM_VECTORDATA_F32S32 158 
#define  ARM_VECTORDATA_F32U16 157 
#define  ARM_VECTORDATA_F32U32 156 
#define  ARM_VECTORDATA_F64 155 
#define  ARM_VECTORDATA_F64F16 154 
#define  ARM_VECTORDATA_F64F32 153 
#define  ARM_VECTORDATA_F64S16 152 
#define  ARM_VECTORDATA_F64S32 151 
#define  ARM_VECTORDATA_F64U16 150 
#define  ARM_VECTORDATA_F64U32 149 
#define  ARM_VECTORDATA_I16 148 
#define  ARM_VECTORDATA_I32 147 
#define  ARM_VECTORDATA_I64 146 
#define  ARM_VECTORDATA_I8 145 
#define  ARM_VECTORDATA_P8 144 
#define  ARM_VECTORDATA_S16 143 
#define  ARM_VECTORDATA_S16F32 142 
#define  ARM_VECTORDATA_S16F64 141 
#define  ARM_VECTORDATA_S32 140 
#define  ARM_VECTORDATA_S32F32 139 
#define  ARM_VECTORDATA_S32F64 138 
#define  ARM_VECTORDATA_S64 137 
#define  ARM_VECTORDATA_S8 136 
#define  ARM_VECTORDATA_U16 135 
#define  ARM_VECTORDATA_U16F32 134 
#define  ARM_VECTORDATA_U16F64 133 
#define  ARM_VECTORDATA_U32 132 
#define  ARM_VECTORDATA_U32F32 131 
#define  ARM_VECTORDATA_U32F64 130 
#define  ARM_VECTORDATA_U64 129 
#define  ARM_VECTORDATA_U8 128 

__attribute__((used)) static const char *vector_data_type_name(arm_vectordata_type type) {
	switch (type) {
	case ARM_VECTORDATA_I8:
		return "i8";
	case ARM_VECTORDATA_I16:
		return "i16";
	case ARM_VECTORDATA_I32:
		return "i32";
	case ARM_VECTORDATA_I64:
		return "i64";
	case ARM_VECTORDATA_S8:
		return "s8";
	case ARM_VECTORDATA_S16:
		return "s16";
	case ARM_VECTORDATA_S32:
		return "s32";
	case ARM_VECTORDATA_S64:
		return "s64";
	case ARM_VECTORDATA_U8:
		return "u8";
	case ARM_VECTORDATA_U16:
		return "u16";
	case ARM_VECTORDATA_U32:
		return "u32";
	case ARM_VECTORDATA_U64:
		return "u64";
	case ARM_VECTORDATA_P8:
		return "p8";
	case ARM_VECTORDATA_F32:
		return "f32";
	case ARM_VECTORDATA_F64:
		return "f64";
	case ARM_VECTORDATA_F16F64:
		return "f16.f64";
	case ARM_VECTORDATA_F64F16:
		return "f64.f16";
	case ARM_VECTORDATA_F32F16:
		return "f32.f16";
	case ARM_VECTORDATA_F16F32:
		return "f16.f32";
	case ARM_VECTORDATA_F64F32:
		return "f64.f32";
	case ARM_VECTORDATA_F32F64:
		return "f32.f64";
	case ARM_VECTORDATA_S32F32:
		return "s32.f32";
	case ARM_VECTORDATA_U32F32:
		return "u32.f32";
	case ARM_VECTORDATA_F32S32:
		return "f32.s32";
	case ARM_VECTORDATA_F32U32:
		return "f32.u32";
	case ARM_VECTORDATA_F64S16:
		return "f64.s16";
	case ARM_VECTORDATA_F32S16:
		return "f32.s16";
	case ARM_VECTORDATA_F64S32:
		return "f64.s32";
	case ARM_VECTORDATA_S16F64:
		return "s16.f64";
	case ARM_VECTORDATA_S16F32:
		return "s16.f64";
	case ARM_VECTORDATA_S32F64:
		return "s32.f64";
	case ARM_VECTORDATA_U16F64:
		return "u16.f64";
	case ARM_VECTORDATA_U16F32:
		return "u16.f32";
	case ARM_VECTORDATA_U32F64:
		return "u32.f64";
	case ARM_VECTORDATA_F64U16:
		return "f64.u16";
	case ARM_VECTORDATA_F32U16:
		return "f32.u16";
	case ARM_VECTORDATA_F64U32:
		return "f64.u32";
	default:
		return "";
	}
}