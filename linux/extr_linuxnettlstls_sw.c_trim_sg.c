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
struct scatterlist {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 

__attribute__((used)) static void trim_sg(struct sock *sk, struct scatterlist *sg,
		    int *sg_num_elem, unsigned int *sg_size, int target_size)
{
	int i = *sg_num_elem - 1;
	int trim = *sg_size - target_size;

	if (trim <= 0) {
		WARN_ON(trim < 0);
		return;
	}

	*sg_size = target_size;
	while (trim >= sg[i].length) {
		trim -= sg[i].length;
		sk_mem_uncharge(sk, sg[i].length);
		put_page(sg_page(&sg[i]));
		i--;

		if (i < 0)
			goto out;
	}

	sg[i].length -= trim;
	sk_mem_uncharge(sk, trim);

out:
	*sg_num_elem = i + 1;
}