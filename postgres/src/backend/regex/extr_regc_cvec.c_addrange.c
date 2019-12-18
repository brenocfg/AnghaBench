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
struct cvec {int nranges; int rangespace; void** ranges; } ;
typedef  void* chr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
addrange(struct cvec *cv,		/* character vector */
		 chr from,				/* first character of range */
		 chr to)				/* last character of range */
{
	assert(cv->nranges < cv->rangespace);
	cv->ranges[cv->nranges * 2] = from;
	cv->ranges[cv->nranges * 2 + 1] = to;
	cv->nranges++;
}