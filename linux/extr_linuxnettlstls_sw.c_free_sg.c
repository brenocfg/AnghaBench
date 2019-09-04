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
struct sock {int dummy; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_sg(struct sock *sk, struct scatterlist *sg,
		    int *sg_num_elem, unsigned int *sg_size)
{
	int i, n = *sg_num_elem;

	for (i = 0; i < n; ++i) {
		sk_mem_uncharge(sk, sg[i].length);
		put_page(sg_page(&sg[i]));
	}
	*sg_num_elem = 0;
	*sg_size = 0;
}