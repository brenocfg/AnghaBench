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
typedef  struct shader_reg {int type; int /*<<< orphan*/  regnum; } const shader_reg ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BWRITERSPR_INPUT ; 
 int BWRITERSPR_TEMP ; 
#define  BWRITERSPR_TEXTURE 128 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T0_REG ; 
 int /*<<< orphan*/  T0_VARYING ; 
 int /*<<< orphan*/  T1_REG ; 
 int /*<<< orphan*/  T1_VARYING ; 
 int /*<<< orphan*/  T2_REG ; 
 int /*<<< orphan*/  T2_VARYING ; 
 int /*<<< orphan*/  T3_REG ; 
 int /*<<< orphan*/  T3_VARYING ; 
 int /*<<< orphan*/  T4_VARYING ; 
 int /*<<< orphan*/  T5_VARYING ; 
 int /*<<< orphan*/  T6_VARYING ; 
 int /*<<< orphan*/  T7_VARYING ; 

__attribute__((used)) static struct shader_reg map_oldps_register(const struct shader_reg *reg, BOOL tex_varying) {
    struct shader_reg ret;
    switch(reg->type) {
        case BWRITERSPR_TEXTURE:
            if(tex_varying) {
                ret = *reg;
                ret.type = BWRITERSPR_INPUT;
                switch(reg->regnum) {
                    case 0:     ret.regnum = T0_VARYING; break;
                    case 1:     ret.regnum = T1_VARYING; break;
                    case 2:     ret.regnum = T2_VARYING; break;
                    case 3:     ret.regnum = T3_VARYING; break;
                    case 4:     ret.regnum = T4_VARYING; break;
                    case 5:     ret.regnum = T5_VARYING; break;
                    case 6:     ret.regnum = T6_VARYING; break;
                    case 7:     ret.regnum = T7_VARYING; break;
                    default:
                        FIXME("Unexpected TEXTURE register t%u\n", reg->regnum);
                        return *reg;
                }
                return ret;
            } else {
                ret = *reg;
                ret.type = BWRITERSPR_TEMP;
                switch(reg->regnum) {
                    case 0:     ret.regnum = T0_REG; break;
                    case 1:     ret.regnum = T1_REG; break;
                    case 2:     ret.regnum = T2_REG; break;
                    case 3:     ret.regnum = T3_REG; break;
                    default:
                        FIXME("Unexpected TEXTURE register t%u\n", reg->regnum);
                        return *reg;
                }
                return ret;
            }

        /* case BWRITERSPR_INPUT - Identical mapping of 1.x/2.0 color varyings
           to 3.0 ones */

        default: return *reg;
    }
}