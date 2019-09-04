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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 struct scatterlist* sg_chain_ptr (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_is_chain (struct scatterlist*) ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct scatterlist *sg_next(struct scatterlist *sg)
{
	if (sg_is_last(sg))
		return NULL;

	sg++;
	if (unlikely(sg_is_chain(sg)))
		sg = sg_chain_ptr(sg);

	return sg;
}