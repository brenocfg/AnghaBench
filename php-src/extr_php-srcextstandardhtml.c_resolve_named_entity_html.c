#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zend_ulong ;
struct TYPE_4__ {size_t num_elems; TYPE_2__** buckets; } ;
typedef  TYPE_1__ entity_ht ;
struct TYPE_5__ {size_t entity_len; unsigned int codepoint1; unsigned int codepoint2; scalar_t__ entity; } ;
typedef  TYPE_2__ entity_cp_map ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 scalar_t__ memcmp (char const*,scalar_t__,size_t) ; 
 size_t zend_inline_hash_func (char const*,size_t) ; 

__attribute__((used)) static inline int resolve_named_entity_html(const char *start, size_t length, const entity_ht *ht, unsigned *uni_cp1, unsigned *uni_cp2)
{
	const entity_cp_map *s;
	zend_ulong hash = zend_inline_hash_func(start, length);

	s = ht->buckets[hash % ht->num_elems];
	while (s->entity) {
		if (s->entity_len == length) {
			if (memcmp(start, s->entity, length) == 0) {
				*uni_cp1 = s->codepoint1;
				*uni_cp2 = s->codepoint2;
				return SUCCESS;
			}
		}
		s++;
	}
	return FAILURE;
}