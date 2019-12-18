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

/* Variables and functions */
 int /*<<< orphan*/  err_set_error_data_int (char*,scalar_t__,int,int) ; 
 scalar_t__ strlen (char*) ; 

void ERR_set_error_data(char *data, int flags)
{
    /*
     * This function is void so we cannot propagate the error return. Since it
     * is also in the public API we can't change the return type.
     *
     * We estimate the size of the data.  If it's not flagged as allocated,
     * then this is safe, and if it is flagged as allocated, then our size
     * may be smaller than the actual allocation, but that doesn't matter
     * too much, the buffer will remain untouched or will eventually be
     * reallocated to a new size.
     *
     * callers should be advised that this function takes over ownership of
     * the allocated memory, i.e. they can't count on the pointer to remain
     * valid.
     */
    err_set_error_data_int(data, strlen(data) + 1, flags, 1);
}