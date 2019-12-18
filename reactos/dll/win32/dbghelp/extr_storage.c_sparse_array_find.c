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
struct sparse_array {int /*<<< orphan*/  elements; } ;
struct key2index {unsigned long key; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct key2index* sparse_array_lookup (struct sparse_array const*,unsigned long,unsigned int*) ; 
 void* vector_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void*   sparse_array_find(const struct sparse_array* sa, unsigned long key)
{
    unsigned            idx;
    struct key2index*   pk2i;

    if ((pk2i = sparse_array_lookup(sa, key, &idx)) && pk2i->key == key)
        return vector_at(&sa->elements, pk2i->index);
    return NULL;
}