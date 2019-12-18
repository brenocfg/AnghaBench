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
typedef  int ULONG ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static inline ULONG read_ulong_be(BYTE* data)
{
    return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
}