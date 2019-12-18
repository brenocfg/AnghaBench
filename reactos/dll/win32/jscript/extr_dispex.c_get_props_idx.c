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
struct TYPE_3__ {int buf_size; } ;
typedef  TYPE_1__ jsdisp_t ;

/* Variables and functions */
 unsigned int GOLDEN_RATIO ; 

__attribute__((used)) static inline unsigned get_props_idx(jsdisp_t *This, unsigned hash)
{
    return (hash*GOLDEN_RATIO) & (This->buf_size-1);
}