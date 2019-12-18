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
struct pstore_record {scalar_t__ type; int id; } ;
struct persistent_ram_zone {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PSTORE_TYPE_DMESG ; 
 int /*<<< orphan*/  persistent_ram_old_size (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  persistent_ram_save_old (struct persistent_ram_zone*) ; 

__attribute__((used)) static struct persistent_ram_zone *
ramoops_get_next_prz(struct persistent_ram_zone *przs[], int id,
		     struct pstore_record *record)
{
	struct persistent_ram_zone *prz;

	/* Give up if we never existed or have hit the end. */
	if (!przs)
		return NULL;

	prz = przs[id];
	if (!prz)
		return NULL;

	/* Update old/shadowed buffer. */
	if (prz->type == PSTORE_TYPE_DMESG)
		persistent_ram_save_old(prz);

	if (!persistent_ram_old_size(prz))
		return NULL;

	record->type = prz->type;
	record->id = id;

	return prz;
}