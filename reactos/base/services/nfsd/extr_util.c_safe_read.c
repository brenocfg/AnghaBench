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

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (void*,unsigned char*,scalar_t__) ; 
 int ERROR_BUFFER_OVERFLOW ; 

int safe_read(unsigned char **pos, uint32_t *remaining, void *dest, uint32_t dest_len) 
{
    if (*remaining < dest_len)
        return ERROR_BUFFER_OVERFLOW;

    CopyMemory(dest, *pos, dest_len);
    *pos += dest_len;
    *remaining -= dest_len;
    return 0;
}