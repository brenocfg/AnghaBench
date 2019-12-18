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
struct d3dx_parameter {int columns; int /*<<< orphan*/  type; scalar_t__ data; } ;
typedef  int UINT ;
typedef  float FLOAT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DXVECTOR4 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  set_number (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_vector(struct d3dx_parameter *param, D3DXVECTOR4 *vector)
{
    UINT i;

    for (i = 0; i < 4; ++i)
    {
        if (i < param->columns)
            set_number((FLOAT *)vector + i, D3DXPT_FLOAT, (DWORD *)param->data + i, param->type);
        else
            ((FLOAT *)vector)[i] = 0.0f;
    }
}