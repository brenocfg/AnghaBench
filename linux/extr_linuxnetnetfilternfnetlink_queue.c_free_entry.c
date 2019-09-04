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
struct nf_queue_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nf_queue_entry*) ; 
 int /*<<< orphan*/  nf_queue_entry_release_refs (struct nf_queue_entry*) ; 

__attribute__((used)) static void free_entry(struct nf_queue_entry *entry)
{
	nf_queue_entry_release_refs(entry);
	kfree(entry);
}