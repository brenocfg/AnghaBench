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
struct dsa_device_ops {int dummy; } ;

/* Variables and functions */
 int DSA_TAG_LAST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOPROTOOPT ; 
 struct dsa_device_ops const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dsa_device_ops** dsa_device_ops ; 

const struct dsa_device_ops *dsa_resolve_tag_protocol(int tag_protocol)
{
	const struct dsa_device_ops *ops;

	if (tag_protocol >= DSA_TAG_LAST)
		return ERR_PTR(-EINVAL);
	ops = dsa_device_ops[tag_protocol];

	if (!ops)
		return ERR_PTR(-ENOPROTOOPT);

	return ops;
}