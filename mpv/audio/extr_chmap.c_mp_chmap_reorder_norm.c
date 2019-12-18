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
typedef  int /*<<< orphan*/  uint8_t ;
struct mp_chmap {int /*<<< orphan*/  num; int /*<<< orphan*/ * speaker; } ;

/* Variables and functions */
 int /*<<< orphan*/  comp_uint8 ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void mp_chmap_reorder_norm(struct mp_chmap *map)
{
    uint8_t *arr = &map->speaker[0];
    qsort(arr, map->num, 1, comp_uint8);
}