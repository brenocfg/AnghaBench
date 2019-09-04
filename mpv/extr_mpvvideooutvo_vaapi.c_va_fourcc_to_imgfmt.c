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
struct fmtentry {scalar_t__ va; int mp; } ;
typedef  enum mp_imgfmt { ____Placeholder_mp_imgfmt } mp_imgfmt ;

/* Variables and functions */
 int IMGFMT_NONE ; 
 struct fmtentry* va_to_imgfmt ; 

__attribute__((used)) static enum mp_imgfmt va_fourcc_to_imgfmt(uint32_t fourcc)
{
    for (const struct fmtentry *entry = va_to_imgfmt; entry->va; ++entry) {
        if (entry->va == fourcc)
            return entry->mp;
    }
    return IMGFMT_NONE;
}