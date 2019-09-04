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

__attribute__((used)) static unsigned
hexval(int c)
{
	if ('0' <= c && c <= '9')
		return (unsigned)(c - '0');
	else if ('a' <= c && c <= 'f')
		return (unsigned)(c - 'a' + 10);
	else if ('A' <= c && c <= 'F')
		return (unsigned)(c - 'A' + 10);
	else
		return 0;
}