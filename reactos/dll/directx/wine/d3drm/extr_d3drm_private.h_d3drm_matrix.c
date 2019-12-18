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
struct d3drm_matrix {int dummy; } ;
typedef  scalar_t__ D3DRMMATRIX4D ;

/* Variables and functions */

__attribute__((used)) static inline struct d3drm_matrix *d3drm_matrix(D3DRMMATRIX4D m)
{
    return (struct d3drm_matrix *)m;
}