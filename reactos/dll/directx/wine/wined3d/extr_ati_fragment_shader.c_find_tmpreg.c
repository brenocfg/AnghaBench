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
typedef  int /*<<< orphan*/  tex_used ;
struct texture_stage_op {scalar_t__ cop; scalar_t__ carg1; scalar_t__ carg2; scalar_t__ carg0; scalar_t__ aarg1; scalar_t__ aarg2; scalar_t__ aarg0; scalar_t__ dst; } ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ GL_NONE ; 
 scalar_t__ GL_REG_0_ATI ; 
 scalar_t__ GL_REG_1_ATI ; 
 int MAX_TEXTURES ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3DTA_TEMP ; 
 scalar_t__ WINED3DTA_TEXTURE ; 
 scalar_t__ WINED3D_TOP_DISABLE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tempreg ; 

__attribute__((used)) static GLuint find_tmpreg(const struct texture_stage_op op[MAX_TEXTURES])
{
    int lowest_read = -1;
    int lowest_write = -1;
    int i;
    BOOL tex_used[MAX_TEXTURES];

    memset(tex_used, 0, sizeof(tex_used));
    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        if (op[i].cop == WINED3D_TOP_DISABLE)
            break;

        if(lowest_read == -1 &&
          (op[i].carg1 == WINED3DTA_TEMP || op[i].carg2 == WINED3DTA_TEMP || op[i].carg0 == WINED3DTA_TEMP ||
           op[i].aarg1 == WINED3DTA_TEMP || op[i].aarg2 == WINED3DTA_TEMP || op[i].aarg0 == WINED3DTA_TEMP)) {
            lowest_read = i;
        }

        if(lowest_write == -1 && op[i].dst == tempreg) {
            lowest_write = i;
        }

        if(op[i].carg1 == WINED3DTA_TEXTURE || op[i].carg2 == WINED3DTA_TEXTURE || op[i].carg0 == WINED3DTA_TEXTURE ||
           op[i].aarg1 == WINED3DTA_TEXTURE || op[i].aarg2 == WINED3DTA_TEXTURE || op[i].aarg0 == WINED3DTA_TEXTURE) {
            tex_used[i] = TRUE;
        }
    }

    /* Temp reg not read? We don't need it, return GL_NONE */
    if(lowest_read == -1) return GL_NONE;

    if(lowest_write >= lowest_read) {
        FIXME("Temp register read before being written\n");
    }

    if(lowest_write == -1) {
        /* This needs a test. Maybe we are supposed to return 0.0/0.0/0.0/0.0, or fail drawprim, or whatever */
        FIXME("Temp register read without being written\n");
        return GL_REG_1_ATI;
    } else if(lowest_write >= 1) {
        /* If we're writing to the temp reg at earliest in stage 1, we can use register 1 for the temp result.
         * there may be texture data stored in reg 1, but we do not need it any longer since stage 1 already
         * read it
         */
        return GL_REG_1_ATI;
    } else {
        /* Search for a free texture register. We have 6 registers available. GL_REG_0_ATI is already used
         * for the regular result
         */
        for(i = 1; i < 6; i++) {
            if(!tex_used[i]) {
                return GL_REG_0_ATI + i;
            }
        }
        /* What to do here? Report it in ValidateDevice? */
        FIXME("Could not find a register for the temporary register\n");
        return 0;
    }
}