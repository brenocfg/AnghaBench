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
#define  BWRITERSIO_ABS 213 
#define  BWRITERSIO_ADD 212 
#define  BWRITERSIO_BEM 211 
#define  BWRITERSIO_BREAK 210 
#define  BWRITERSIO_BREAKC 209 
#define  BWRITERSIO_BREAKP 208 
#define  BWRITERSIO_CALL 207 
#define  BWRITERSIO_CALLNZ 206 
#define  BWRITERSIO_CMP 205 
#define  BWRITERSIO_CND 204 
#define  BWRITERSIO_COMMENT 203 
#define  BWRITERSIO_CRS 202 
#define  BWRITERSIO_DCL 201 
#define  BWRITERSIO_DEF 200 
#define  BWRITERSIO_DEFB 199 
#define  BWRITERSIO_DEFI 198 
#define  BWRITERSIO_DP2ADD 197 
#define  BWRITERSIO_DP3 196 
#define  BWRITERSIO_DP4 195 
#define  BWRITERSIO_DST 194 
#define  BWRITERSIO_DSX 193 
#define  BWRITERSIO_DSY 192 
#define  BWRITERSIO_ELSE 191 
#define  BWRITERSIO_END 190 
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
 int D3DSIO_ABS ; 
 int D3DSIO_ADD ; 
 int D3DSIO_BEM ; 
 int D3DSIO_BREAK ; 
 int D3DSIO_BREAKC ; 
 int D3DSIO_BREAKP ; 
 int D3DSIO_CALL ; 
 int D3DSIO_CALLNZ ; 
 int D3DSIO_CMP ; 
 int D3DSIO_CND ; 
 int D3DSIO_COMMENT ; 
 int D3DSIO_CRS ; 
 int D3DSIO_DCL ; 
 int D3DSIO_DEF ; 
 int D3DSIO_DEFB ; 
 int D3DSIO_DEFI ; 
 int D3DSIO_DP2ADD ; 
 int D3DSIO_DP3 ; 
 int D3DSIO_DP4 ; 
 int D3DSIO_DST ; 
 int D3DSIO_DSX ; 
 int D3DSIO_DSY ; 
 int D3DSIO_ELSE ; 
 int D3DSIO_END ; 
 int D3DSIO_ENDIF ; 
 int D3DSIO_ENDLOOP ; 
 int D3DSIO_ENDREP ; 
 int D3DSIO_EXP ; 
 int D3DSIO_EXPP ; 
 int D3DSIO_FRC ; 
 int D3DSIO_IF ; 
 int D3DSIO_IFC ; 
 int D3DSIO_LABEL ; 
 int D3DSIO_LIT ; 
 int D3DSIO_LOG ; 
 int D3DSIO_LOGP ; 
 int D3DSIO_LOOP ; 
 int D3DSIO_LRP ; 
 int D3DSIO_M3x2 ; 
 int D3DSIO_M3x3 ; 
 int D3DSIO_M3x4 ; 
 int D3DSIO_M4x3 ; 
 int D3DSIO_M4x4 ; 
 int D3DSIO_MAD ; 
 int D3DSIO_MAX ; 
 int D3DSIO_MIN ; 
 int D3DSIO_MOV ; 
 int D3DSIO_MOVA ; 
 int D3DSIO_MUL ; 
 int D3DSIO_NOP ; 
 int D3DSIO_NRM ; 
 int D3DSIO_PHASE ; 
 int D3DSIO_POW ; 
 int D3DSIO_RCP ; 
 int D3DSIO_REP ; 
 int D3DSIO_RET ; 
 int D3DSIO_RSQ ; 
 int D3DSIO_SETP ; 
 int D3DSIO_SGE ; 
 int D3DSIO_SGN ; 
 int D3DSIO_SINCOS ; 
 int D3DSIO_SLT ; 
 int D3DSIO_SUB ; 
 int D3DSIO_TEX ; 
 int D3DSIO_TEXBEM ; 
 int D3DSIO_TEXBEML ; 
 int D3DSIO_TEXCOORD ; 
 int D3DSIO_TEXDEPTH ; 
 int D3DSIO_TEXDP3 ; 
 int D3DSIO_TEXDP3TEX ; 
 int D3DSIO_TEXKILL ; 
 int D3DSIO_TEXLDD ; 
 int D3DSIO_TEXLDL ; 
 int D3DSIO_TEXM3x2DEPTH ; 
 int D3DSIO_TEXM3x2PAD ; 
 int D3DSIO_TEXM3x2TEX ; 
 int D3DSIO_TEXM3x3 ; 
 int D3DSIO_TEXM3x3PAD ; 
 int D3DSIO_TEXM3x3SPEC ; 
 int D3DSIO_TEXM3x3TEX ; 
 int D3DSIO_TEXM3x3VSPEC ; 
 int D3DSIO_TEXREG2AR ; 
 int D3DSIO_TEXREG2GB ; 
 int D3DSIO_TEXREG2RGB ; 
 int D3DSI_TEXLD_BIAS ; 
 int D3DSI_TEXLD_PROJECT ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static DWORD d3d9_opcode(DWORD bwriter_opcode)
{
    switch (bwriter_opcode)
    {
        case BWRITERSIO_NOP:         return D3DSIO_NOP;
        case BWRITERSIO_MOV:         return D3DSIO_MOV;
        case BWRITERSIO_ADD:         return D3DSIO_ADD;
        case BWRITERSIO_SUB:         return D3DSIO_SUB;
        case BWRITERSIO_MAD:         return D3DSIO_MAD;
        case BWRITERSIO_MUL:         return D3DSIO_MUL;
        case BWRITERSIO_RCP:         return D3DSIO_RCP;
        case BWRITERSIO_RSQ:         return D3DSIO_RSQ;
        case BWRITERSIO_DP3:         return D3DSIO_DP3;
        case BWRITERSIO_DP4:         return D3DSIO_DP4;
        case BWRITERSIO_MIN:         return D3DSIO_MIN;
        case BWRITERSIO_MAX:         return D3DSIO_MAX;
        case BWRITERSIO_SLT:         return D3DSIO_SLT;
        case BWRITERSIO_SGE:         return D3DSIO_SGE;
        case BWRITERSIO_EXP:         return D3DSIO_EXP;
        case BWRITERSIO_LOG:         return D3DSIO_LOG;
        case BWRITERSIO_LIT:         return D3DSIO_LIT;
        case BWRITERSIO_DST:         return D3DSIO_DST;
        case BWRITERSIO_LRP:         return D3DSIO_LRP;
        case BWRITERSIO_FRC:         return D3DSIO_FRC;
        case BWRITERSIO_M4x4:        return D3DSIO_M4x4;
        case BWRITERSIO_M4x3:        return D3DSIO_M4x3;
        case BWRITERSIO_M3x4:        return D3DSIO_M3x4;
        case BWRITERSIO_M3x3:        return D3DSIO_M3x3;
        case BWRITERSIO_M3x2:        return D3DSIO_M3x2;
        case BWRITERSIO_CALL:        return D3DSIO_CALL;
        case BWRITERSIO_CALLNZ:      return D3DSIO_CALLNZ;
        case BWRITERSIO_LOOP:        return D3DSIO_LOOP;
        case BWRITERSIO_RET:         return D3DSIO_RET;
        case BWRITERSIO_ENDLOOP:     return D3DSIO_ENDLOOP;
        case BWRITERSIO_LABEL:       return D3DSIO_LABEL;
        case BWRITERSIO_DCL:         return D3DSIO_DCL;
        case BWRITERSIO_POW:         return D3DSIO_POW;
        case BWRITERSIO_CRS:         return D3DSIO_CRS;
        case BWRITERSIO_SGN:         return D3DSIO_SGN;
        case BWRITERSIO_ABS:         return D3DSIO_ABS;
        case BWRITERSIO_NRM:         return D3DSIO_NRM;
        case BWRITERSIO_SINCOS:      return D3DSIO_SINCOS;
        case BWRITERSIO_REP:         return D3DSIO_REP;
        case BWRITERSIO_ENDREP:      return D3DSIO_ENDREP;
        case BWRITERSIO_IF:          return D3DSIO_IF;
        case BWRITERSIO_IFC:         return D3DSIO_IFC;
        case BWRITERSIO_ELSE:        return D3DSIO_ELSE;
        case BWRITERSIO_ENDIF:       return D3DSIO_ENDIF;
        case BWRITERSIO_BREAK:       return D3DSIO_BREAK;
        case BWRITERSIO_BREAKC:      return D3DSIO_BREAKC;
        case BWRITERSIO_MOVA:        return D3DSIO_MOVA;
        case BWRITERSIO_DEFB:        return D3DSIO_DEFB;
        case BWRITERSIO_DEFI:        return D3DSIO_DEFI;

        case BWRITERSIO_TEXCOORD:    return D3DSIO_TEXCOORD;
        case BWRITERSIO_TEXKILL:     return D3DSIO_TEXKILL;
        case BWRITERSIO_TEX:         return D3DSIO_TEX;
        case BWRITERSIO_TEXBEM:      return D3DSIO_TEXBEM;
        case BWRITERSIO_TEXBEML:     return D3DSIO_TEXBEML;
        case BWRITERSIO_TEXREG2AR:   return D3DSIO_TEXREG2AR;
        case BWRITERSIO_TEXREG2GB:   return D3DSIO_TEXREG2GB;
        case BWRITERSIO_TEXM3x2PAD:  return D3DSIO_TEXM3x2PAD;
        case BWRITERSIO_TEXM3x2TEX:  return D3DSIO_TEXM3x2TEX;
        case BWRITERSIO_TEXM3x3PAD:  return D3DSIO_TEXM3x3PAD;
        case BWRITERSIO_TEXM3x3TEX:  return D3DSIO_TEXM3x3TEX;
        case BWRITERSIO_TEXM3x3SPEC: return D3DSIO_TEXM3x3SPEC;
        case BWRITERSIO_TEXM3x3VSPEC:return D3DSIO_TEXM3x3VSPEC;
        case BWRITERSIO_EXPP:        return D3DSIO_EXPP;
        case BWRITERSIO_LOGP:        return D3DSIO_LOGP;
        case BWRITERSIO_CND:         return D3DSIO_CND;
        case BWRITERSIO_DEF:         return D3DSIO_DEF;
        case BWRITERSIO_TEXREG2RGB:  return D3DSIO_TEXREG2RGB;
        case BWRITERSIO_TEXDP3TEX:   return D3DSIO_TEXDP3TEX;
        case BWRITERSIO_TEXM3x2DEPTH:return D3DSIO_TEXM3x2DEPTH;
        case BWRITERSIO_TEXDP3:      return D3DSIO_TEXDP3;
        case BWRITERSIO_TEXM3x3:     return D3DSIO_TEXM3x3;
        case BWRITERSIO_TEXDEPTH:    return D3DSIO_TEXDEPTH;
        case BWRITERSIO_CMP:         return D3DSIO_CMP;
        case BWRITERSIO_BEM:         return D3DSIO_BEM;
        case BWRITERSIO_DP2ADD:      return D3DSIO_DP2ADD;
        case BWRITERSIO_DSX:         return D3DSIO_DSX;
        case BWRITERSIO_DSY:         return D3DSIO_DSY;
        case BWRITERSIO_TEXLDD:      return D3DSIO_TEXLDD;
        case BWRITERSIO_SETP:        return D3DSIO_SETP;
        case BWRITERSIO_TEXLDL:      return D3DSIO_TEXLDL;
        case BWRITERSIO_BREAKP:      return D3DSIO_BREAKP;

        case BWRITERSIO_PHASE:       return D3DSIO_PHASE;
        case BWRITERSIO_COMMENT:     return D3DSIO_COMMENT;
        case BWRITERSIO_END:         return D3DSIO_END;

        case BWRITERSIO_TEXLDP:      return D3DSIO_TEX | D3DSI_TEXLD_PROJECT;
        case BWRITERSIO_TEXLDB:      return D3DSIO_TEX | D3DSI_TEXLD_BIAS;

        default:
            FIXME("Unhandled BWRITERSIO token %#x.\n", bwriter_opcode);
            return ~0U;
    }
}