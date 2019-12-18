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
 int /*<<< orphan*/  nf_conntrack_helper_unregister (struct nf_conntrack_helper*) ; 

void nf_conntrack_helpers_unregister(struct nf_conntrack_helper *helper,
				unsigned int n)
{
	while (n-- > 0)
		nf_conntrack_helper_unregister(&helper[n]);
}