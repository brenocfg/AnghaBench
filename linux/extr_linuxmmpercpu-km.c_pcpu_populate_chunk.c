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
struct pcpu_chunk {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */

__attribute__((used)) static int pcpu_populate_chunk(struct pcpu_chunk *chunk,
			       int page_start, int page_end, gfp_t gfp)
{
	return 0;
}