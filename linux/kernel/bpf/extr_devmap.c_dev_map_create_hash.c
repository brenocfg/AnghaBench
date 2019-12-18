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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (struct hlist_head*) ; 
 struct hlist_head* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *dev_map_create_hash(unsigned int entries)
{
	int i;
	struct hlist_head *hash;

	hash = kmalloc_array(entries, sizeof(*hash), GFP_KERNEL);
	if (hash != NULL)
		for (i = 0; i < entries; i++)
			INIT_HLIST_HEAD(&hash[i]);

	return hash;
}