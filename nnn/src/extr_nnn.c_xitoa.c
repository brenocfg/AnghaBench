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
typedef  int uint ;

/* Variables and functions */

__attribute__((used)) static char *xitoa(uint val)
{
	static char ascbuf[32] = {0};
	int i = 30;

	if (!val)
		return "0";

	for (; val && i; --i, val /= 10)
		ascbuf[i] = '0' + (val % 10);

	return &ascbuf[++i];
}