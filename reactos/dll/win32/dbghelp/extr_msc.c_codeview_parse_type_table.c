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
struct TYPE_2__ {int id; } ;
union codeview_type {TYPE_1__ generic; } ;
struct codeview_type_parse {unsigned int num; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int FIRST_DEFINABLE_TYPE ; 
 int /*<<< orphan*/  TRUE ; 
 union codeview_type* codeview_jump_to_type (struct codeview_type_parse*,unsigned int) ; 
 int /*<<< orphan*/  codeview_parse_one_type (struct codeview_type_parse*,unsigned int,union codeview_type const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL codeview_parse_type_table(struct codeview_type_parse* ctp)
{
    unsigned int                curr_type = FIRST_DEFINABLE_TYPE;
    const union codeview_type*  type;

    for (curr_type = FIRST_DEFINABLE_TYPE; curr_type < FIRST_DEFINABLE_TYPE + ctp->num; curr_type++)
    {
        type = codeview_jump_to_type(ctp, curr_type);

        /* type records we're interested in are the ones referenced by symbols
         * The known ranges are (X mark the ones we want):
         *   X  0000-0016       for V1 types
         *      0200-020c       for V1 types referenced by other types
         *      0400-040f       for V1 types (complex lists & sets)
         *   X  1000-100f       for V2 types
         *      1200-120c       for V2 types referenced by other types
         *      1400-140f       for V1 types (complex lists & sets)
         *   X  1500-150d       for V3 types
         *      8000-8010       for numeric leafes
         */
        if (!(type->generic.id & 0x8600) || (type->generic.id & 0x0100))
            codeview_parse_one_type(ctp, curr_type, type, TRUE);
    }

    return TRUE;
}