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
struct d3dx_parameter {scalar_t__ columns; int /*<<< orphan*/  type; scalar_t__ data; } ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  FLOAT ;
typedef  int /*<<< orphan*/  D3DXVECTOR4 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  set_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_vector(struct d3dx_parameter *param, const D3DXVECTOR4 *vector)
{
    UINT i;

    for (i = 0; i < param->columns; ++i)
    {
        set_number((FLOAT *)param->data + i, param->type, (FLOAT *)vector + i, D3DXPT_FLOAT);
    }
}