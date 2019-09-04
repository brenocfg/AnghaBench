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
struct compressor_entry {int /*<<< orphan*/  list; struct compressor* comp; } ;
struct compressor {int /*<<< orphan*/  compress_proto; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  compressor_list ; 
 int /*<<< orphan*/  compressor_list_lock ; 
 scalar_t__ find_comp_entry (int /*<<< orphan*/ ) ; 
 struct compressor_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
ppp_register_compressor(struct compressor *cp)
{
	struct compressor_entry *ce;
	int ret;
	spin_lock(&compressor_list_lock);
	ret = -EEXIST;
	if (find_comp_entry(cp->compress_proto))
		goto out;
	ret = -ENOMEM;
	ce = kmalloc(sizeof(struct compressor_entry), GFP_ATOMIC);
	if (!ce)
		goto out;
	ret = 0;
	ce->comp = cp;
	list_add(&ce->list, &compressor_list);
 out:
	spin_unlock(&compressor_list_lock);
	return ret;
}