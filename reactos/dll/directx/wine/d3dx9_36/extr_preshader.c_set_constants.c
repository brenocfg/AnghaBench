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
struct d3dx_regstore {scalar_t__* tables; } ;
struct d3dx_parameter {unsigned int* data; int rows; int columns; int /*<<< orphan*/  type; } ;
struct d3dx_const_tab {unsigned int const_set_count; struct d3dx_const_param_eval_output* const_set; int /*<<< orphan*/  update_version; } ;
struct d3dx_const_param_eval_output {int table; unsigned int register_index; unsigned int register_count; scalar_t__ constant_class; unsigned int element_count; struct d3dx_parameter* param; scalar_t__ direct_copy; } ;
struct const_upload_info {unsigned int major_count; unsigned int minor; unsigned int major_stride; unsigned int major; unsigned int minor_remainder; scalar_t__ transpose; } ;
struct IDirect3DDevice9 {int dummy; } ;
typedef  enum pres_value_type { ____Placeholder_pres_value_type } pres_value_type ;
typedef  enum pres_reg_tables { ____Placeholder_pres_reg_tables } pres_reg_tables ;
typedef  int /*<<< orphan*/  ULONG64 ;
struct TYPE_2__ {int type; } ;
typedef  int /*<<< orphan*/  ID3DXEffectStateManager ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DXPARAMETER_TYPE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ D3DXPC_SCALAR ; 
 scalar_t__ D3DXPC_VECTOR ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PRES_REGTAB_COUNT ; 
 int /*<<< orphan*/  get_const_upload_info (struct d3dx_const_param_eval_output*,struct const_upload_info*) ; 
 int get_offset_reg (int,unsigned int) ; 
 unsigned int get_reg_components (int) ; 
 int is_param_dirty (struct d3dx_parameter*,int /*<<< orphan*/ ) ; 
 unsigned int max (int,int) ; 
 int /*<<< orphan*/  regstore_set_data (struct d3dx_regstore*,int,unsigned int,unsigned int*,int,int) ; 
 int /*<<< orphan*/  regstore_set_values (struct d3dx_regstore*,int,unsigned int*,unsigned int,int) ; 
 int /*<<< orphan*/  set_constants_device (int /*<<< orphan*/ *,struct IDirect3DDevice9*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 TYPE_1__* table_info ; 
 int table_type_from_param_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT set_constants(struct d3dx_regstore *rs, struct d3dx_const_tab *const_tab,
        ULONG64 new_update_version, ID3DXEffectStateManager *manager, struct IDirect3DDevice9 *device,
        D3DXPARAMETER_TYPE type, BOOL device_update_all, BOOL pres_dirty)
{
    unsigned int const_idx;
    unsigned int current_start = 0, current_count = 0;
    enum pres_reg_tables current_table = PRES_REGTAB_COUNT;
    BOOL update_device = manager || device;
    HRESULT hr, result = D3D_OK;
    ULONG64 update_version = const_tab->update_version;

    for (const_idx = 0; const_idx < const_tab->const_set_count; ++const_idx)
    {
        struct d3dx_const_param_eval_output *const_set = &const_tab->const_set[const_idx];
        enum pres_reg_tables table = const_set->table;
        struct d3dx_parameter *param = const_set->param;
        unsigned int element, i, j, start_offset;
        struct const_upload_info info;
        unsigned int *data;
        enum pres_value_type param_type;

        if (!(param && is_param_dirty(param, update_version)))
            continue;

        data = param->data;
        start_offset = get_offset_reg(table, const_set->register_index);
        if (const_set->direct_copy)
        {
            regstore_set_values(rs, table, data, start_offset,
                    get_offset_reg(table, const_set->register_count));
            continue;
        }
        param_type = table_type_from_param_type(param->type);
        if (const_set->constant_class == D3DXPC_SCALAR || const_set->constant_class == D3DXPC_VECTOR)
        {
            unsigned int count = max(param->rows, param->columns);

            if (count >= get_reg_components(table))
            {
                regstore_set_data(rs, table, start_offset, data,
                        count * const_set->element_count, param_type);
            }
            else
            {
                for (element = 0; element < const_set->element_count; ++element)
                    regstore_set_data(rs, table, start_offset + get_offset_reg(table, element),
                            &data[element * count], count, param_type);
            }
            continue;
        }
        get_const_upload_info(const_set, &info);
        for (element = 0; element < const_set->element_count; ++element)
        {
            unsigned int *out = (unsigned int *)rs->tables[table] + start_offset;

            /* Store reshaped but (possibly) not converted yet data temporarily in the same constants buffer.
             * All the supported types of parameters and table values have the same size. */
            if (info.transpose)
            {
                for (i = 0; i < info.major_count; ++i)
                    for (j = 0; j < info.minor; ++j)
                        out[i * info.major_stride + j] = data[i + j * info.major];

                for (j = 0; j < info.minor_remainder; ++j)
                    out[i * info.major_stride + j] = data[i + j * info.major];
            }
            else
            {
                for (i = 0; i < info.major_count; ++i)
                    for (j = 0; j < info.minor; ++j)
                        out[i * info.major_stride + j] = data[i * info.minor + j];
            }
            start_offset += get_offset_reg(table, const_set->register_count);
            data += param->rows * param->columns;
        }
        start_offset = get_offset_reg(table, const_set->register_index);
        if (table_info[table].type != param_type)
            regstore_set_data(rs, table, start_offset, (unsigned int *)rs->tables[table] + start_offset,
                    get_offset_reg(table, const_set->register_count) * const_set->element_count, param_type);
    }
    const_tab->update_version = new_update_version;
    if (!update_device)
        return D3D_OK;

    for (const_idx = 0; const_idx < const_tab->const_set_count; ++const_idx)
    {
        struct d3dx_const_param_eval_output *const_set = &const_tab->const_set[const_idx];

        if (device_update_all || (const_set->param
                ? is_param_dirty(const_set->param, update_version) : pres_dirty))
        {
            enum pres_reg_tables table = const_set->table;

            if (table == current_table && current_start + current_count == const_set->register_index)
            {
                current_count += const_set->register_count * const_set->element_count;
            }
            else
            {
                if (current_count)
                {
                    if (FAILED(hr = set_constants_device(manager, device, type, current_table,
                            (DWORD *)rs->tables[current_table]
                            + get_offset_reg(current_table, current_start), current_start, current_count)))
                        result = hr;
                }
                current_table = table;
                current_start = const_set->register_index;
                current_count = const_set->register_count * const_set->element_count;
            }
        }
    }
    if (current_count)
    {
        if (FAILED(hr = set_constants_device(manager, device, type, current_table,
                (DWORD *)rs->tables[current_table]
                + get_offset_reg(current_table, current_start), current_start, current_count)))
            result = hr;
    }
    return result;
}