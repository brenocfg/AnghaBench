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
struct shader_reg {int type; int regnum; } ;

/* Variables and functions */
#define  BWRITERSPR_ADDR 148 
#define  BWRITERSPR_ATTROUT 147 
#define  BWRITERSPR_COLOROUT 146 
#define  BWRITERSPR_CONST 145 
#define  BWRITERSPR_CONSTBOOL 144 
#define  BWRITERSPR_CONSTINT 143 
#define  BWRITERSPR_DEPTHOUT 142 
#define  BWRITERSPR_INPUT 141 
#define  BWRITERSPR_LABEL 140 
#define  BWRITERSPR_LOOP 139 
#define  BWRITERSPR_MISCTYPE 138 
#define  BWRITERSPR_OUTPUT 137 
#define  BWRITERSPR_PREDICATE 136 
#define  BWRITERSPR_RASTOUT 135 
#define  BWRITERSPR_SAMPLER 134 
#define  BWRITERSPR_TEMP 133 
#define  BWRITERSPR_TEXCRDOUT 132 
#define  BWRITERSPR_TEXTURE 131 
#define  BWRITERSRO_FOG 130 
#define  BWRITERSRO_POINT_SIZE 129 
#define  BWRITERSRO_POSITION 128 
 char const* wine_dbg_sprintf (char*,int) ; 

__attribute__((used)) static const char *get_regname(const struct shader_reg *reg)
{
    switch (reg->type)
    {
        case BWRITERSPR_TEMP:
            return wine_dbg_sprintf("r%u", reg->regnum);
        case BWRITERSPR_INPUT:
            return wine_dbg_sprintf("v%u", reg->regnum);
        case BWRITERSPR_CONST:
            return wine_dbg_sprintf("c%u", reg->regnum);
        case BWRITERSPR_ADDR:
            return wine_dbg_sprintf("a%u", reg->regnum);
        case BWRITERSPR_TEXTURE:
            return wine_dbg_sprintf("t%u", reg->regnum);
        case BWRITERSPR_RASTOUT:
            switch (reg->regnum)
            {
                case BWRITERSRO_POSITION:   return "oPos";
                case BWRITERSRO_FOG:        return "oFog";
                case BWRITERSRO_POINT_SIZE: return "oPts";
                default: return "Unexpected RASTOUT";
            }
        case BWRITERSPR_ATTROUT:
            return wine_dbg_sprintf("oD%u", reg->regnum);
        case BWRITERSPR_TEXCRDOUT:
            return wine_dbg_sprintf("oT%u", reg->regnum);
        case BWRITERSPR_OUTPUT:
            return wine_dbg_sprintf("o%u", reg->regnum);
        case BWRITERSPR_CONSTINT:
            return wine_dbg_sprintf("i%u", reg->regnum);
        case BWRITERSPR_COLOROUT:
            return wine_dbg_sprintf("oC%u", reg->regnum);
        case BWRITERSPR_DEPTHOUT:
            return "oDepth";
        case BWRITERSPR_SAMPLER:
            return wine_dbg_sprintf("s%u", reg->regnum);
        case BWRITERSPR_CONSTBOOL:
            return wine_dbg_sprintf("b%u", reg->regnum);
        case BWRITERSPR_LOOP:
            return "aL";
        case BWRITERSPR_MISCTYPE:
            switch (reg->regnum)
            {
                case 0: return "vPos";
                case 1: return "vFace";
                default: return "unexpected misctype";
            }
        case BWRITERSPR_LABEL:
            return wine_dbg_sprintf("l%u", reg->regnum);
        case BWRITERSPR_PREDICATE:
            return wine_dbg_sprintf("p%u", reg->regnum);
        default:
            return wine_dbg_sprintf("unknown regname %#x", reg->type);
    }
}