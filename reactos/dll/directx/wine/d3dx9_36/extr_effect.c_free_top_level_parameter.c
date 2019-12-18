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
struct d3dx_top_level_parameter {unsigned int annotation_count; int /*<<< orphan*/  param; int /*<<< orphan*/ * annotations; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3dx_pool_release_shared_parameter (struct d3dx_top_level_parameter*) ; 
 int /*<<< orphan*/  free_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_top_level_parameter(struct d3dx_top_level_parameter *param)
{
    if (param->annotations)
    {
        unsigned int i;

        for (i = 0; i < param->annotation_count; ++i)
            free_parameter(&param->annotations[i], FALSE, FALSE);
        HeapFree(GetProcessHeap(), 0, param->annotations);
    }
    d3dx_pool_release_shared_parameter(param);
    free_parameter(&param->param, FALSE, FALSE);
}