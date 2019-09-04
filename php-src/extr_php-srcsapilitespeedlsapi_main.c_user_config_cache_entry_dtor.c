#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  user_config; } ;
typedef  TYPE_1__ user_config_cache_entry ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_config_cache_entry_dtor(zval *el)
{
    user_config_cache_entry *entry = (user_config_cache_entry *)Z_PTR_P(el);
    zend_hash_destroy(&entry->user_config);
    free(entry);
}