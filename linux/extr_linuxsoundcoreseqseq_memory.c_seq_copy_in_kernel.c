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
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 

__attribute__((used)) static int seq_copy_in_kernel(char **bufptr, const void *src, int size)
{
	memcpy(*bufptr, src, size);
	*bufptr += size;
	return 0;
}