#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct d3dx_parameter {int class; int bytes; int columns; scalar_t__ data; int /*<<< orphan*/  type; int /*<<< orphan*/  element_count; } ;
struct d3dx9_base_effect {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  w; int /*<<< orphan*/  x; int /*<<< orphan*/  y; int /*<<< orphan*/  z; } ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ D3DXVECTOR4 ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
#define  D3DXPC_MATRIX_ROWS 132 
#define  D3DXPC_OBJECT 131 
#define  D3DXPC_SCALAR 130 
#define  D3DXPC_STRUCT 129 
#define  D3DXPC_VECTOR 128 
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  D3DXPT_INT ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int INT_FLOAT_MULTI ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (int) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  set_dirty (struct d3dx_parameter*) ; 
 int /*<<< orphan*/  set_vector (struct d3dx_parameter*,TYPE_1__ const*) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_set_vector(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, const D3DXVECTOR4 *vector)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (param && !param->element_count)
    {
        TRACE("Class %s\n", debug_d3dxparameter_class(param->class));

        switch (param->class)
        {
            case D3DXPC_SCALAR:
            case D3DXPC_VECTOR:
                set_dirty(param);
                if (param->type == D3DXPT_INT && param->bytes == 4)
                {
                    DWORD tmp;

                    TRACE("INT fixup\n");
                    tmp = (DWORD)(max(min(vector->z, 1.0f), 0.0f) * INT_FLOAT_MULTI);
                    tmp += ((DWORD)(max(min(vector->y, 1.0f), 0.0f) * INT_FLOAT_MULTI)) << 8;
                    tmp += ((DWORD)(max(min(vector->x, 1.0f), 0.0f) * INT_FLOAT_MULTI)) << 16;
                    tmp += ((DWORD)(max(min(vector->w, 1.0f), 0.0f) * INT_FLOAT_MULTI)) << 24;

                    *(INT *)param->data = tmp;
                    return D3D_OK;
                }
                if (param->type == D3DXPT_FLOAT)
                {
                    memcpy(param->data, vector, param->columns * sizeof(float));
                    return D3D_OK;
                }

                set_vector(param, vector);
                return D3D_OK;

            case D3DXPC_MATRIX_ROWS:
            case D3DXPC_OBJECT:
            case D3DXPC_STRUCT:
                break;

            default:
                FIXME("Unhandled class %s\n", debug_d3dxparameter_class(param->class));
                break;
        }
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}