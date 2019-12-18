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
struct pernet_operations {int /*<<< orphan*/ * id; scalar_t__ size; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ops_free(const struct pernet_operations *ops, struct net *net)
{
	if (ops->id && ops->size) {
		kfree(net_generic(net, *ops->id));
	}
}