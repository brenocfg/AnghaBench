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
struct net {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int VPORT_HASH_BUCKETS ; 
 struct hlist_head* dev_table ; 
 unsigned int jhash (char const*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct hlist_head *hash_bucket(const struct net *net, const char *name)
{
	unsigned int hash = jhash(name, strlen(name), (unsigned long) net);
	return &dev_table[hash & (VPORT_HASH_BUCKETS - 1)];
}