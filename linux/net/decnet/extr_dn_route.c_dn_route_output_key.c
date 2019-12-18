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
struct flowidn {scalar_t__ flowidn_proto; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int PTR_ERR (struct dst_entry*) ; 
 int __dn_route_output_key (struct dst_entry**,struct flowidn*,int) ; 
 int /*<<< orphan*/  flowidn_to_flowi (struct flowidn*) ; 
 int /*<<< orphan*/  init_net ; 
 struct dst_entry* xfrm_lookup (int /*<<< orphan*/ *,struct dst_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_route_output_key(struct dst_entry **pprt, struct flowidn *flp, int flags)
{
	int err;

	err = __dn_route_output_key(pprt, flp, flags);
	if (err == 0 && flp->flowidn_proto) {
		*pprt = xfrm_lookup(&init_net, *pprt,
				    flowidn_to_flowi(flp), NULL, 0);
		if (IS_ERR(*pprt)) {
			err = PTR_ERR(*pprt);
			*pprt = NULL;
		}
	}
	return err;
}