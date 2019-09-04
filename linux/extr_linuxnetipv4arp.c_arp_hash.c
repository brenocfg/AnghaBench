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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  arp_hashfn (void const*,struct net_device const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 arp_hash(const void *pkey,
		    const struct net_device *dev,
		    __u32 *hash_rnd)
{
	return arp_hashfn(pkey, dev, hash_rnd);
}