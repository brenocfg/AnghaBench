#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3dx_regstore {unsigned int* table_sizes; } ;
struct TYPE_4__ {unsigned int table; unsigned int offset; } ;
struct TYPE_3__ {scalar_t__ table; unsigned int offset; } ;
struct d3dx_pres_operand {TYPE_2__ reg; TYPE_1__ index_reg; } ;

/* Variables and functions */
 unsigned int PRES_REGTAB_CONST ; 
 scalar_t__ PRES_REGTAB_COUNT ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 double exec_get_reg_value (struct d3dx_regstore*,unsigned int,unsigned int) ; 
 unsigned int get_offset_reg (unsigned int,unsigned int) ; 
 unsigned int get_reg_components (unsigned int) ; 
 unsigned int get_reg_offset (unsigned int,unsigned int) ; 
 unsigned int lrint (double) ; 

__attribute__((used)) static double exec_get_arg(struct d3dx_regstore *rs, const struct d3dx_pres_operand *opr, unsigned int comp)
{
    unsigned int offset, base_index, reg_index, table;

    table = opr->reg.table;

    if (opr->index_reg.table == PRES_REGTAB_COUNT)
        base_index = 0;
    else
        base_index = lrint(exec_get_reg_value(rs, opr->index_reg.table, opr->index_reg.offset));

    offset = get_offset_reg(table, base_index) + opr->reg.offset + comp;
    reg_index = get_reg_offset(table, offset);

    if (reg_index >= rs->table_sizes[table])
    {
        unsigned int wrap_size;

        if (table == PRES_REGTAB_CONST)
        {
            /* As it can be guessed from tests, offset into floating constant table is wrapped
             * to the nearest power of 2 and not to the actual table size. */
            for (wrap_size = 1; wrap_size < rs->table_sizes[table]; wrap_size <<= 1)
                ;
        }
        else
        {
            wrap_size = rs->table_sizes[table];
        }
        WARN("Wrapping register index %u, table %u, wrap_size %u, table size %u.\n",
                reg_index, table, wrap_size, rs->table_sizes[table]);
        reg_index %= wrap_size;

        if (reg_index >= rs->table_sizes[table])
            return 0.0;

        offset = get_offset_reg(table, reg_index) + offset % get_reg_components(table);
    }

    return exec_get_reg_value(rs, table, offset);
}