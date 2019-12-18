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
typedef  int /*<<< orphan*/  D3DXVECTOR2 ;

/* Variables and functions */
 int /*<<< orphan*/ * D3DXVec2Normalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3DXVec2Subtract (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline D3DXVECTOR2 *unit_vec2(D3DXVECTOR2 *dir, const D3DXVECTOR2 *pt1, const D3DXVECTOR2 *pt2)
{
    return D3DXVec2Normalize(D3DXVec2Subtract(dir, pt2, pt1), dir);
}