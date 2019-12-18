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
struct nf_conntrack_tuple {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_conntrack_raw (struct nf_conntrack_tuple const*,struct net const*) ; 
 int /*<<< orphan*/  scale_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hash_conntrack(const struct net *net,
			  const struct nf_conntrack_tuple *tuple)
{
	return scale_hash(hash_conntrack_raw(tuple, net));
}