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
struct keyitem_pair {int /*<<< orphan*/  item; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (struct keyitem_pair*) ; 

__attribute__((used)) static void free_keyitem_pair(struct keyitem_pair *pair)
{
    VariantClear(&pair->key);
    VariantClear(&pair->item);
    heap_free(pair);
}