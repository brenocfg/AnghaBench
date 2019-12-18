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
struct TYPE_3__ {size_t len; int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ h16 ;
typedef  int USHORT ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ hex_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static USHORT h16tous(h16 component) {
    DWORD i;
    USHORT ret = 0;

    for(i = 0; i < component.len; ++i) {
        ret <<= 4;
        ret += hex_to_int(component.str[i]);
    }

    return ret;
}