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
typedef  int DWORD ;

/* Variables and functions */
#define  BWRITERSIO_ABS 211 
#define  BWRITERSIO_ADD 210 
#define  BWRITERSIO_BEM 209 
#define  BWRITERSIO_BREAK 208 
#define  BWRITERSIO_BREAKC 207 
#define  BWRITERSIO_BREAKP 206 
#define  BWRITERSIO_CALL 205 
#define  BWRITERSIO_CALLNZ 204 
#define  BWRITERSIO_CMP 203 
#define  BWRITERSIO_CND 202 
#define  BWRITERSIO_CRS 201 
#define  BWRITERSIO_DCL 200 
#define  BWRITERSIO_DEF 199 
#define  BWRITERSIO_DEFB 198 
#define  BWRITERSIO_DEFI 197 
#define  BWRITERSIO_DP2ADD 196 
#define  BWRITERSIO_DP3 195 
#define  BWRITERSIO_DP4 194 
#define  BWRITERSIO_DST 193 
#define  BWRITERSIO_DSX 192 
#define  BWRITERSIO_DSY 191 
#define  BWRITERSIO_ELSE 190 
#define  BWRITERSIO_ENDIF 189 
#define  BWRITERSIO_ENDLOOP 188 
#define  BWRITERSIO_ENDREP 187 
#define  BWRITERSIO_EXP 186 
#define  BWRITERSIO_EXPP 185 
#define  BWRITERSIO_FRC 184 
#define  BWRITERSIO_IF 183 
#define  BWRITERSIO_IFC 182 
#define  BWRITERSIO_LABEL 181 
#define  BWRITERSIO_LIT 180 
#define  BWRITERSIO_LOG 179 
#define  BWRITERSIO_LOGP 178 
#define  BWRITERSIO_LOOP 177 
#define  BWRITERSIO_LRP 176 
#define  BWRITERSIO_M3x2 175 
#define  BWRITERSIO_M3x3 174 
#define  BWRITERSIO_M3x4 173 
#define  BWRITERSIO_M4x3 172 
#define  BWRITERSIO_M4x4 171 
#define  BWRITERSIO_MAD 170 
#define  BWRITERSIO_MAX 169 
#define  BWRITERSIO_MIN 168 
#define  BWRITERSIO_MOV 167 
#define  BWRITERSIO_MOVA 166 
#define  BWRITERSIO_MUL 165 
#define  BWRITERSIO_NOP 164 
#define  BWRITERSIO_NRM 163 
#define  BWRITERSIO_PHASE 162 
#define  BWRITERSIO_POW 161 
#define  BWRITERSIO_RCP 160 
#define  BWRITERSIO_REP 159 
#define  BWRITERSIO_RET 158 
#define  BWRITERSIO_RSQ 157 
#define  BWRITERSIO_SETP 156 
#define  BWRITERSIO_SGE 155 
#define  BWRITERSIO_SGN 154 
#define  BWRITERSIO_SINCOS 153 
#define  BWRITERSIO_SLT 152 
#define  BWRITERSIO_SUB 151 
#define  BWRITERSIO_TEX 150 
#define  BWRITERSIO_TEXBEM 149 
#define  BWRITERSIO_TEXBEML 148 
#define  BWRITERSIO_TEXCOORD 147 
#define  BWRITERSIO_TEXDEPTH 146 
#define  BWRITERSIO_TEXDP3 145 
#define  BWRITERSIO_TEXDP3TEX 144 
#define  BWRITERSIO_TEXKILL 143 
#define  BWRITERSIO_TEXLDB 142 
#define  BWRITERSIO_TEXLDD 141 
#define  BWRITERSIO_TEXLDL 140 
#define  BWRITERSIO_TEXLDP 139 
#define  BWRITERSIO_TEXM3x2DEPTH 138 
#define  BWRITERSIO_TEXM3x2PAD 137 
#define  BWRITERSIO_TEXM3x2TEX 136 
#define  BWRITERSIO_TEXM3x3 135 
#define  BWRITERSIO_TEXM3x3PAD 134 
#define  BWRITERSIO_TEXM3x3SPEC 133 
#define  BWRITERSIO_TEXM3x3TEX 132 
#define  BWRITERSIO_TEXM3x3VSPEC 131 
#define  BWRITERSIO_TEXREG2AR 130 
#define  BWRITERSIO_TEXREG2GB 129 
#define  BWRITERSIO_TEXREG2RGB 128 

const char *debug_print_opcode(DWORD opcode)
{
    switch (opcode)
    {
        case BWRITERSIO_NOP:          return "nop";
        case BWRITERSIO_MOV:          return "mov";
        case BWRITERSIO_ADD:          return "add";
        case BWRITERSIO_SUB:          return "sub";
        case BWRITERSIO_MAD:          return "mad";
        case BWRITERSIO_MUL:          return "mul";
        case BWRITERSIO_RCP:          return "rcp";
        case BWRITERSIO_RSQ:          return "rsq";
        case BWRITERSIO_DP3:          return "dp3";
        case BWRITERSIO_DP4:          return "dp4";
        case BWRITERSIO_MIN:          return "min";
        case BWRITERSIO_MAX:          return "max";
        case BWRITERSIO_SLT:          return "slt";
        case BWRITERSIO_SGE:          return "sge";
        case BWRITERSIO_EXP:          return "exp";
        case BWRITERSIO_LOG:          return "log";
        case BWRITERSIO_LIT:          return "lit";
        case BWRITERSIO_DST:          return "dst";
        case BWRITERSIO_LRP:          return "lrp";
        case BWRITERSIO_FRC:          return "frc";
        case BWRITERSIO_M4x4:         return "m4x4";
        case BWRITERSIO_M4x3:         return "m4x3";
        case BWRITERSIO_M3x4:         return "m3x4";
        case BWRITERSIO_M3x3:         return "m3x3";
        case BWRITERSIO_M3x2:         return "m3x2";
        case BWRITERSIO_CALL:         return "call";
        case BWRITERSIO_CALLNZ:       return "callnz";
        case BWRITERSIO_LOOP:         return "loop";
        case BWRITERSIO_RET:          return "ret";
        case BWRITERSIO_ENDLOOP:      return "endloop";
        case BWRITERSIO_LABEL:        return "label";
        case BWRITERSIO_DCL:          return "dcl";
        case BWRITERSIO_POW:          return "pow";
        case BWRITERSIO_CRS:          return "crs";
        case BWRITERSIO_SGN:          return "sgn";
        case BWRITERSIO_ABS:          return "abs";
        case BWRITERSIO_NRM:          return "nrm";
        case BWRITERSIO_SINCOS:       return "sincos";
        case BWRITERSIO_REP:          return "rep";
        case BWRITERSIO_ENDREP:       return "endrep";
        case BWRITERSIO_IF:           return "if";
        case BWRITERSIO_IFC:          return "ifc";
        case BWRITERSIO_ELSE:         return "else";
        case BWRITERSIO_ENDIF:        return "endif";
        case BWRITERSIO_BREAK:        return "break";
        case BWRITERSIO_BREAKC:       return "breakc";
        case BWRITERSIO_MOVA:         return "mova";
        case BWRITERSIO_DEFB:         return "defb";
        case BWRITERSIO_DEFI:         return "defi";
        case BWRITERSIO_TEXCOORD:     return "texcoord";
        case BWRITERSIO_TEXKILL:      return "texkill";
        case BWRITERSIO_TEX:          return "tex";
        case BWRITERSIO_TEXBEM:       return "texbem";
        case BWRITERSIO_TEXBEML:      return "texbeml";
        case BWRITERSIO_TEXREG2AR:    return "texreg2ar";
        case BWRITERSIO_TEXREG2GB:    return "texreg2gb";
        case BWRITERSIO_TEXM3x2PAD:   return "texm3x2pad";
        case BWRITERSIO_TEXM3x2TEX:   return "texm3x2tex";
        case BWRITERSIO_TEXM3x3PAD:   return "texm3x3pad";
        case BWRITERSIO_TEXM3x3TEX:   return "texm3x3tex";
        case BWRITERSIO_TEXM3x3SPEC:  return "texm3x3vspec";
        case BWRITERSIO_TEXM3x3VSPEC: return "texm3x3vspec";
        case BWRITERSIO_EXPP:         return "expp";
        case BWRITERSIO_LOGP:         return "logp";
        case BWRITERSIO_CND:          return "cnd";
        case BWRITERSIO_DEF:          return "def";
        case BWRITERSIO_TEXREG2RGB:   return "texreg2rgb";
        case BWRITERSIO_TEXDP3TEX:    return "texdp3tex";
        case BWRITERSIO_TEXM3x2DEPTH: return "texm3x2depth";
        case BWRITERSIO_TEXDP3:       return "texdp3";
        case BWRITERSIO_TEXM3x3:      return "texm3x3";
        case BWRITERSIO_TEXDEPTH:     return "texdepth";
        case BWRITERSIO_CMP:          return "cmp";
        case BWRITERSIO_BEM:          return "bem";
        case BWRITERSIO_DP2ADD:       return "dp2add";
        case BWRITERSIO_DSX:          return "dsx";
        case BWRITERSIO_DSY:          return "dsy";
        case BWRITERSIO_TEXLDD:       return "texldd";
        case BWRITERSIO_SETP:         return "setp";
        case BWRITERSIO_TEXLDL:       return "texldl";
        case BWRITERSIO_BREAKP:       return "breakp";
        case BWRITERSIO_PHASE:        return "phase";

        case BWRITERSIO_TEXLDP:       return "texldp";
        case BWRITERSIO_TEXLDB:       return "texldb";

        default:                      return "unknown";
    }
}