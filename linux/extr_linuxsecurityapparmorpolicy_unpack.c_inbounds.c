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
struct aa_ext {size_t end; size_t pos; } ;

/* Variables and functions */

__attribute__((used)) static bool inbounds(struct aa_ext *e, size_t size)
{
	return (size <= e->end - e->pos);
}