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
struct TYPE_3__ {int* data; } ;
typedef  TYPE_1__ dwarf2_traverse_context_t ;

/* Variables and functions */

__attribute__((used)) static unsigned dwarf2_leb128_length(const dwarf2_traverse_context_t* ctx)
{
    unsigned    ret;
    for (ret = 0; ctx->data[ret] & 0x80; ret++);
    return ret + 1;
}