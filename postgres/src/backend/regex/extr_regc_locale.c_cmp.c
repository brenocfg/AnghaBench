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
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int /*<<< orphan*/  VS (int /*<<< orphan*/  const*) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int						/* 0 for equal, nonzero for unequal */
cmp(const chr *x, const chr *y, /* strings to compare */
	size_t len)					/* exact length of comparison */
{
	return memcmp(VS(x), VS(y), len * sizeof(chr));
}