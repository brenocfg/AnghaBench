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
struct shader_reg {unsigned int type; scalar_t__ regnum; scalar_t__ rel_reg; } ;
struct allowed_reg_type {unsigned int type; scalar_t__ count; scalar_t__ reladdr; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL check_reg_type(const struct shader_reg *reg,
                           const struct allowed_reg_type *allowed) {
    unsigned int i = 0;

    while(allowed[i].type != ~0U) {
        if(reg->type == allowed[i].type) {
            if(reg->rel_reg) {
                if(allowed[i].reladdr)
                    return TRUE; /* The relative addressing register
                                    can have a negative value, we
                                    can't check the register index */
                return FALSE;
            }
            if(reg->regnum < allowed[i].count) return TRUE;
            return FALSE;
        }
        i++;
    }
    return FALSE;
}