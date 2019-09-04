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
struct net {struct hlist_head* dev_name_head; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  NETDEV_HASHBITS ; 
 unsigned int full_name_hash (struct net*,char const*,int /*<<< orphan*/ ) ; 
 size_t hash_32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnlen (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_head *dev_name_hash(struct net *net, const char *name)
{
	unsigned int hash = full_name_hash(net, name, strnlen(name, IFNAMSIZ));

	return &net->dev_name_head[hash_32(hash, NETDEV_HASHBITS)];
}