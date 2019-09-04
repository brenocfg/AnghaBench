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
typedef  int /*<<< orphan*/  spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/ ** spl_array_get_hash_table_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HashTable *spl_array_get_hash_table(spl_array_object* intern) { /* {{{ */
	return *spl_array_get_hash_table_ptr(intern);
}