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
typedef  scalar_t__ __u8 ;
typedef  int BOOLEAN ;

/* Variables and functions */

__attribute__((used)) static __inline BOOLEAN Ext2IsNullUuid (__u8 * uuid)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (uuid[i]) {
            break;
        }
    }

    return (i >= 16);
}