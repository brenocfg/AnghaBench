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
typedef  enum ra_blend { ____Placeholder_ra_blend } ra_blend ;
typedef  int /*<<< orphan*/  D3D11_BLEND ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_BLEND_INV_SRC_ALPHA ; 
 int /*<<< orphan*/  D3D11_BLEND_ONE ; 
 int /*<<< orphan*/  D3D11_BLEND_SRC_ALPHA ; 
 int /*<<< orphan*/  D3D11_BLEND_ZERO ; 
#define  RA_BLEND_ONE 131 
#define  RA_BLEND_ONE_MINUS_SRC_ALPHA 130 
#define  RA_BLEND_SRC_ALPHA 129 
#define  RA_BLEND_ZERO 128 

__attribute__((used)) static D3D11_BLEND map_ra_blend(enum ra_blend blend)
{
    switch (blend) {
    default:
    case RA_BLEND_ZERO:                return D3D11_BLEND_ZERO;
    case RA_BLEND_ONE:                 return D3D11_BLEND_ONE;
    case RA_BLEND_SRC_ALPHA:           return D3D11_BLEND_SRC_ALPHA;
    case RA_BLEND_ONE_MINUS_SRC_ALPHA: return D3D11_BLEND_INV_SRC_ALPHA;
    };
}