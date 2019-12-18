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
struct TYPE_2__ {scalar_t__ fmt; } ;

/* Variables and functions */
 int COMP_ID__NONE ; 
 TYPE_1__* compressions ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int is_supported_compression(const char *ext)
{
	unsigned i;

	for (i = 1; compressions[i].fmt; i++) {
		if (!strcmp(ext, compressions[i].fmt))
			return i;
	}
	return COMP_ID__NONE;
}