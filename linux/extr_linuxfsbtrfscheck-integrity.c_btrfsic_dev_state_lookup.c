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
struct btrfsic_dev_state {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  btrfsic_dev_state_hashtable ; 
 struct btrfsic_dev_state* btrfsic_dev_state_hashtable_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfsic_dev_state *btrfsic_dev_state_lookup(dev_t dev)
{
	return btrfsic_dev_state_hashtable_lookup(dev,
						  &btrfsic_dev_state_hashtable);
}