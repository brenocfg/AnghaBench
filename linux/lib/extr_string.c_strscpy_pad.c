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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strscpy (char*,char const*,size_t) ; 

ssize_t strscpy_pad(char *dest, const char *src, size_t count)
{
	ssize_t written;

	written = strscpy(dest, src, count);
	if (written < 0 || written == count - 1)
		return written;

	memset(dest + written + 1, 0, count - written - 1);

	return written;
}