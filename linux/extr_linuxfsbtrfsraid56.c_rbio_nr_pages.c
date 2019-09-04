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
 int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 

__attribute__((used)) static unsigned long rbio_nr_pages(unsigned long stripe_len, int nr_stripes)
{
	return DIV_ROUND_UP(stripe_len, PAGE_SIZE) * nr_stripes;
}