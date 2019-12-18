#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  writemask; } ;
typedef  struct shader_reg {int type; int /*<<< orphan*/  regnum; TYPE_1__ u; } const shader_reg ;

/* Variables and functions */
#define  BWRITERSPR_ATTROUT 133 
 void* BWRITERSPR_OUTPUT ; 
#define  BWRITERSPR_RASTOUT 132 
#define  BWRITERSPR_TEXCRDOUT 131 
#define  BWRITERSRO_FOG 130 
#define  BWRITERSRO_POINT_SIZE 129 
#define  BWRITERSRO_POSITION 128 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OD0_REG ; 
 int /*<<< orphan*/  OD1_REG ; 
 int /*<<< orphan*/  OFOG_REG ; 
 int /*<<< orphan*/  OFOG_WRITEMASK ; 
 int /*<<< orphan*/  OPOS_REG ; 
 int /*<<< orphan*/  OPTS_REG ; 
 int /*<<< orphan*/  OPTS_WRITEMASK ; 
 int /*<<< orphan*/  OT0_REG ; 
 int /*<<< orphan*/  OT1_REG ; 
 int /*<<< orphan*/  OT2_REG ; 
 int /*<<< orphan*/  OT3_REG ; 
 int /*<<< orphan*/  OT4_REG ; 
 int /*<<< orphan*/  OT5_REG ; 
 int /*<<< orphan*/  OT6_REG ; 
 int /*<<< orphan*/  OT7_REG ; 

__attribute__((used)) static struct shader_reg map_oldvs_register(const struct shader_reg *reg) {
    struct shader_reg ret;
    switch(reg->type) {
        case BWRITERSPR_RASTOUT:
            ret = *reg;
            ret.type = BWRITERSPR_OUTPUT;
            switch(reg->regnum) {
                case BWRITERSRO_POSITION:
                    ret.regnum = OPOS_REG;
                    break;
                case BWRITERSRO_FOG:
                    ret.regnum = OFOG_REG;
                    ret.u.writemask = OFOG_WRITEMASK;
                    break;
                case BWRITERSRO_POINT_SIZE:
                    ret.regnum = OPTS_REG;
                    ret.u.writemask = OPTS_WRITEMASK;
                    break;
                default:
                    FIXME("Unhandled RASTOUT register %u\n", reg->regnum);
                    return *reg;
            }
            return ret;

        case BWRITERSPR_TEXCRDOUT:
            ret = *reg;
            ret.type = BWRITERSPR_OUTPUT;
            switch(reg->regnum) {
                case 0: ret.regnum = OT0_REG; break;
                case 1: ret.regnum = OT1_REG; break;
                case 2: ret.regnum = OT2_REG; break;
                case 3: ret.regnum = OT3_REG; break;
                case 4: ret.regnum = OT4_REG; break;
                case 5: ret.regnum = OT5_REG; break;
                case 6: ret.regnum = OT6_REG; break;
                case 7: ret.regnum = OT7_REG; break;
                default:
                    FIXME("Unhandled TEXCRDOUT regnum %u\n", reg->regnum);
                    return *reg;
            }
            return ret;

        case BWRITERSPR_ATTROUT:
            ret = *reg;
            ret.type = BWRITERSPR_OUTPUT;
            switch(reg->regnum) {
                case 0: ret.regnum = OD0_REG; break;
                case 1: ret.regnum = OD1_REG; break;
                default:
                    FIXME("Unhandled ATTROUT regnum %u\n", reg->regnum);
                    return *reg;
            }
            return ret;

        default: return *reg;
    }
}