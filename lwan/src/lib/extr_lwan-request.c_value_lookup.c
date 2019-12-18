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
struct lwan_key_value_array {int dummy; } ;
struct lwan_key_value {char* key; void* value; } ;
struct lwan_array {struct lwan_key_value* elements; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  k ;

/* Variables and functions */
 scalar_t__ LIKELY (struct lwan_key_value*) ; 
 struct lwan_key_value* bsearch (struct lwan_key_value*,int /*<<< orphan*/ ,struct lwan_key_value*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_value_compare ; 

__attribute__((used)) static inline void *
value_lookup(const struct lwan_key_value_array *array, const char *key)
{
    const struct lwan_array *la = (const struct lwan_array *)array;

    if (LIKELY(la->elements)) {
        struct lwan_key_value k = { .key = (char *)key };
        struct lwan_key_value *entry;

        entry = bsearch(&k, la->base, la->elements, sizeof(k), key_value_compare);
        if (LIKELY(entry))
            return entry->value;
    }

    return NULL;
}