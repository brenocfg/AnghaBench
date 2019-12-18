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
struct d3dx_parameter {scalar_t__ element_count; int class; int /*<<< orphan*/ * members; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  D3DXMATRIX ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
#define  D3DXPC_MATRIX_ROWS 131 
#define  D3DXPC_OBJECT 130 
#define  D3DXPC_SCALAR 129 
#define  D3DXPC_VECTOR 128 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (int) ; 
 int /*<<< orphan*/  get_matrix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_matrix_pointer_array(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, D3DXMATRIX **matrix, UINT count)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (!count) return D3D_OK;

    if (param && matrix && count <= param->element_count)
    {
        UINT i;

        TRACE("Class %s\n", debug_d3dxparameter_class(param->class));

        switch (param->class)
        {
            case D3DXPC_MATRIX_ROWS:
                for (i = 0; i < count; ++i)
                {
                    get_matrix(&param->members[i], matrix[i], FALSE);
                }
                return D3D_OK;

            case D3DXPC_SCALAR:
            case D3DXPC_VECTOR:
            case D3DXPC_OBJECT:
                break;

            default:
                FIXME("Unhandled class %s\n", debug_d3dxparameter_class(param->class));
                break;
        }
    }

    WARN("Parameter not found.\n");

    return D3DERR_INVALIDCALL;
}