#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ source_type; scalar_t__ target_type; scalar_t__ target_class; int specified; } ;
struct avtab_datum {int dummy; } ;
struct avtab_node {TYPE_1__ key; struct avtab_datum datum; struct avtab_node* next; } ;
struct avtab_key {int specified; scalar_t__ source_type; scalar_t__ target_type; scalar_t__ target_class; } ;
struct avtab {struct avtab_node** htable; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int AVTAB_ENABLED ; 
 int AVTAB_ENABLED_OLD ; 
 int avtab_hash (struct avtab_key*,int /*<<< orphan*/ ) ; 

struct avtab_datum *avtab_search(struct avtab *h, struct avtab_key *key)
{
	int hvalue;
	struct avtab_node *cur;
	u16 specified = key->specified & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	if (!h)
		return NULL;

	hvalue = avtab_hash(key, h->mask);
	for (cur = h->htable[hvalue]; cur;
	     cur = cur->next) {
		if (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specified & cur->key.specified))
			return &cur->datum;

		if (key->source_type < cur->key.source_type)
			break;
		if (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			break;
		if (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			break;
	}

	return NULL;
}