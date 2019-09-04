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
struct automic_entry {scalar_t__ attr; } ;

/* Variables and functions */

__attribute__((used)) static int compare_attr(const void *ap, const void *bp)
{
	const struct automic_entry *a = ap;
	const struct automic_entry *b = bp;
	return (int)(a->attr - b->attr);
}