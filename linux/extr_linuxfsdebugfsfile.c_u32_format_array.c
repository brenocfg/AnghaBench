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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t snprintf (char*,size_t,char*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static size_t u32_format_array(char *buf, size_t bufsize,
			       u32 *array, int array_size)
{
	size_t ret = 0;

	while (--array_size >= 0) {
		size_t len;
		char term = array_size ? ' ' : '\n';

		len = snprintf(buf, bufsize, "%u%c", *array++, term);
		ret += len;

		buf += len;
		bufsize -= len;
	}
	return ret;
}