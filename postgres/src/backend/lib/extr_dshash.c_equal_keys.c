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
struct TYPE_4__ {scalar_t__ (* compare_function ) (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  key_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  arg; TYPE_1__ params; } ;
typedef  TYPE_2__ dshash_table ;

/* Variables and functions */
 scalar_t__ stub1 (void const*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
equal_keys(dshash_table *hash_table, const void *a, const void *b)
{
	return hash_table->params.compare_function(a, b,
											   hash_table->params.key_size,
											   hash_table->arg) == 0;
}