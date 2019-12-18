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
typedef  scalar_t__ uint32_t ;
struct fmtentry {int mp; scalar_t__ va; } ;

/* Variables and functions */
 struct fmtentry* va_to_imgfmt ; 

__attribute__((used)) static uint32_t va_fourcc_from_imgfmt(int imgfmt)
{
    for (const struct fmtentry *entry = va_to_imgfmt; entry->va; ++entry) {
        if (entry->mp == imgfmt)
            return entry->va;
    }
    return 0;
}