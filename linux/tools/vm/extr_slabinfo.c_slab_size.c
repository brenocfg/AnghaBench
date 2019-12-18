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
struct slabinfo {unsigned long slabs; unsigned long order; } ;

/* Variables and functions */
 unsigned long page_size ; 

__attribute__((used)) static unsigned long slab_size(struct slabinfo *s)
{
	return 	s->slabs * (page_size << s->order);
}