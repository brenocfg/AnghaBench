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
struct nf_conntrack_helper {int dummy; } ;

/* Variables and functions */
 int nf_conntrack_helper_register (struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  nf_conntrack_helpers_unregister (struct nf_conntrack_helper*,unsigned int) ; 

int nf_conntrack_helpers_register(struct nf_conntrack_helper *helper,
				  unsigned int n)
{
	unsigned int i;
	int err = 0;

	for (i = 0; i < n; i++) {
		err = nf_conntrack_helper_register(&helper[i]);
		if (err < 0)
			goto err;
	}

	return err;
err:
	if (i > 0)
		nf_conntrack_helpers_unregister(helper, i);
	return err;
}