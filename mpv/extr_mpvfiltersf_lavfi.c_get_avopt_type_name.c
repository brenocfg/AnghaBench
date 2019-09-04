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
typedef  enum AVOptionType { ____Placeholder_AVOptionType } AVOptionType ;

/* Variables and functions */
#define  AV_OPT_TYPE_BINARY 146 
#define  AV_OPT_TYPE_BOOL 145 
#define  AV_OPT_TYPE_CHANNEL_LAYOUT 144 
#define  AV_OPT_TYPE_COLOR 143 
#define  AV_OPT_TYPE_CONST 142 
#define  AV_OPT_TYPE_DICT 141 
#define  AV_OPT_TYPE_DOUBLE 140 
#define  AV_OPT_TYPE_DURATION 139 
#define  AV_OPT_TYPE_FLAGS 138 
#define  AV_OPT_TYPE_FLOAT 137 
#define  AV_OPT_TYPE_IMAGE_SIZE 136 
#define  AV_OPT_TYPE_INT 135 
#define  AV_OPT_TYPE_INT64 134 
#define  AV_OPT_TYPE_PIXEL_FMT 133 
#define  AV_OPT_TYPE_RATIONAL 132 
#define  AV_OPT_TYPE_SAMPLE_FMT 131 
#define  AV_OPT_TYPE_STRING 130 
#define  AV_OPT_TYPE_UINT64 129 
#define  AV_OPT_TYPE_VIDEO_RATE 128 

__attribute__((used)) static const char *get_avopt_type_name(enum AVOptionType type)
{
    switch (type) {
    case AV_OPT_TYPE_FLAGS:             return "flags";
    case AV_OPT_TYPE_INT:               return "int";
    case AV_OPT_TYPE_INT64:             return "int64";
    case AV_OPT_TYPE_DOUBLE:            return "double";
    case AV_OPT_TYPE_FLOAT:             return "float";
    case AV_OPT_TYPE_STRING:            return "string";
    case AV_OPT_TYPE_RATIONAL:          return "rational";
    case AV_OPT_TYPE_BINARY:            return "binary";
    case AV_OPT_TYPE_DICT:              return "dict";
    case AV_OPT_TYPE_UINT64:            return "uint64";
    case AV_OPT_TYPE_IMAGE_SIZE:        return "imagesize";
    case AV_OPT_TYPE_PIXEL_FMT:         return "pixfmt";
    case AV_OPT_TYPE_SAMPLE_FMT:        return "samplefmt";
    case AV_OPT_TYPE_VIDEO_RATE:        return "fps";
    case AV_OPT_TYPE_DURATION:          return "duration";
    case AV_OPT_TYPE_COLOR:             return "color";
    case AV_OPT_TYPE_CHANNEL_LAYOUT:    return "channellayout";
    case AV_OPT_TYPE_BOOL:              return "bool";
    case AV_OPT_TYPE_CONST: // fallthrough
    default:
        return NULL;
    }
}