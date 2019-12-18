#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nRefs; scalar_t__ nAge; } ;
typedef  TYPE_1__ ME_FontCacheItem ;

/* Variables and functions */

__attribute__((used)) static void release_font_cache(ME_FontCacheItem *item)
{
    if (item->nRefs > 0)
    {
        item->nRefs--;
        item->nAge = 0;
    }
}