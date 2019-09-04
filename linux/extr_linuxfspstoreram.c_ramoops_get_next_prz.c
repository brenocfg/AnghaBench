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
typedef  int uint ;
typedef  int u64 ;
struct persistent_ram_zone {int dummy; } ;
typedef  enum pstore_type_id { ____Placeholder_pstore_type_id } pstore_type_id ;

/* Variables and functions */
 int /*<<< orphan*/  persistent_ram_old_size (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  persistent_ram_save_old (struct persistent_ram_zone*) ; 

__attribute__((used)) static struct persistent_ram_zone *
ramoops_get_next_prz(struct persistent_ram_zone *przs[], uint *c, uint max,
		     u64 *id,
		     enum pstore_type_id *typep, enum pstore_type_id type,
		     bool update)
{
	struct persistent_ram_zone *prz;
	int i = (*c)++;

	/* Give up if we never existed or have hit the end. */
	if (!przs || i >= max)
		return NULL;

	prz = przs[i];
	if (!prz)
		return NULL;

	/* Update old/shadowed buffer. */
	if (update)
		persistent_ram_save_old(prz);

	if (!persistent_ram_old_size(prz))
		return NULL;

	*typep = type;
	*id = i;

	return prz;
}