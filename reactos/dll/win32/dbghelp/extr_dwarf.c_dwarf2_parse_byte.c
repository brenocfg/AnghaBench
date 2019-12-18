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
struct TYPE_3__ {int data; } ;
typedef  TYPE_1__ dwarf2_traverse_context_t ;

/* Variables and functions */
 unsigned char dwarf2_get_byte (int) ; 

__attribute__((used)) static unsigned char dwarf2_parse_byte(dwarf2_traverse_context_t* ctx)
{
    unsigned char uvalue = dwarf2_get_byte(ctx->data);
    ctx->data += 1;
    return uvalue;
}