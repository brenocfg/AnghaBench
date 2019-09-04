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
struct nf_queue_entry {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct nf_queue_entry* kmemdup (struct nf_queue_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_queue_entry_get_refs (struct nf_queue_entry*) ; 

__attribute__((used)) static struct nf_queue_entry *
nf_queue_entry_dup(struct nf_queue_entry *e)
{
	struct nf_queue_entry *entry = kmemdup(e, e->size, GFP_ATOMIC);
	if (entry)
		nf_queue_entry_get_refs(entry);
	return entry;
}