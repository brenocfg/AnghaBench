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
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conncount_data {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 unsigned int count_tree (struct net*,struct nf_conncount_data*,int /*<<< orphan*/  const*,struct nf_conntrack_tuple const*,struct nf_conntrack_zone const*) ; 

unsigned int nf_conncount_count(struct net *net,
				struct nf_conncount_data *data,
				const u32 *key,
				const struct nf_conntrack_tuple *tuple,
				const struct nf_conntrack_zone *zone)
{
	return count_tree(net, data, key, tuple, zone);
}