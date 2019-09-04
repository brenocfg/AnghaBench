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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int active_cacheline_read_overlap (int /*<<< orphan*/ ) ; 
 int active_cacheline_set_overlap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int active_cacheline_dec_overlap(phys_addr_t cln)
{
	int overlap = active_cacheline_read_overlap(cln);

	return active_cacheline_set_overlap(cln, --overlap);
}