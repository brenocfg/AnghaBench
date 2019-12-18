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
typedef  int Size ;

/* Variables and functions */

__attribute__((used)) static char *
qtext_fetch(Size query_offset, int query_len,
			char *buffer, Size buffer_size)
{
	/* File read failed? */
	if (buffer == NULL)
		return NULL;
	/* Bogus offset/length? */
	if (query_len < 0 ||
		query_offset + query_len >= buffer_size)
		return NULL;
	/* As a further sanity check, make sure there's a trailing null */
	if (buffer[query_offset + query_len] != '\0')
		return NULL;
	/* Looks OK */
	return buffer + query_offset;
}