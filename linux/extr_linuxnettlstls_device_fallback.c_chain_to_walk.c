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
struct scatterlist {int offset; scalar_t__ length; } ;
struct scatter_walk {int offset; struct scatterlist* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  scatterwalk_crypto_chain (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void chain_to_walk(struct scatterlist *sg, struct scatter_walk *walk)
{
	struct scatterlist *src = walk->sg;
	int diff = walk->offset - src->offset;

	sg_set_page(sg, sg_page(src),
		    src->length - diff, walk->offset);

	scatterwalk_crypto_chain(sg, sg_next(src), 2);
}