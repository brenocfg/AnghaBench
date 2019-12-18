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
 unsigned int SG_MAX_SINGLE_ALLOC ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  kmemleak_free (struct scatterlist*) ; 

__attribute__((used)) static void sg_kfree(struct scatterlist *sg, unsigned int nents)
{
	if (nents == SG_MAX_SINGLE_ALLOC) {
		kmemleak_free(sg);
		free_page((unsigned long) sg);
	} else
		kfree(sg);
}