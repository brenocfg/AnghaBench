#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* dents ; 
 scalar_t__ xstrcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dentfind(const char *fname, int n)
{
	int i = 0;

	for (; i < n; ++i)
		if (xstrcmp(fname, dents[i].name) == 0)
			return i;

	return 0;
}