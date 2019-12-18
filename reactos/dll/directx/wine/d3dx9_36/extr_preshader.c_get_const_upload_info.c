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
struct d3dx_parameter {scalar_t__ class; unsigned int columns; unsigned int rows; } ;
struct d3dx_const_param_eval_output {unsigned int table; scalar_t__ constant_class; unsigned int register_count; struct d3dx_parameter* param; } ;
struct const_upload_info {int transpose; unsigned int major; unsigned int minor; unsigned int major_stride; unsigned int major_count; unsigned int minor_remainder; unsigned int count; } ;

/* Variables and functions */
 scalar_t__ D3DXPC_MATRIX_COLUMNS ; 
 scalar_t__ D3DXPC_MATRIX_ROWS ; 
 unsigned int get_offset_reg (unsigned int,unsigned int) ; 
 int get_reg_components (unsigned int) ; 

__attribute__((used)) static void get_const_upload_info(struct d3dx_const_param_eval_output *const_set,
        struct const_upload_info *info)
{
    struct d3dx_parameter *param = const_set->param;
    unsigned int table = const_set->table;

    info->transpose = (const_set->constant_class == D3DXPC_MATRIX_COLUMNS && param->class == D3DXPC_MATRIX_ROWS)
            || (param->class == D3DXPC_MATRIX_COLUMNS && const_set->constant_class == D3DXPC_MATRIX_ROWS);
    if (const_set->constant_class == D3DXPC_MATRIX_COLUMNS)
    {
        info->major = param->columns;
        info->minor = param->rows;
    }
    else
    {
        info->major = param->rows;
        info->minor = param->columns;
    }

    if (get_reg_components(table) == 1)
    {
        unsigned int const_length = get_offset_reg(table, const_set->register_count);

        info->major_stride = info->minor;
        info->major_count = const_length / info->major_stride;
        info->minor_remainder = const_length % info->major_stride;
    }
    else
    {
        info->major_stride = get_reg_components(table);
        info->major_count = const_set->register_count;
        info->minor_remainder = 0;
    }
    info->count = info->major_count * info->minor + info->minor_remainder;
}