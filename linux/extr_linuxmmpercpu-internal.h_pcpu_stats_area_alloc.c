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

/* Variables and functions */

__attribute__((used)) static inline void pcpu_stats_area_alloc(struct pcpu_chunk *chunk, size_t size)
{
}