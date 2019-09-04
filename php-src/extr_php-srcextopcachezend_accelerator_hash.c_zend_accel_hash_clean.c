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
typedef  int /*<<< orphan*/  zend_accel_hash_entry ;
struct TYPE_3__ {int max_num_entries; int /*<<< orphan*/  hash_table; scalar_t__ num_direct_entries; scalar_t__ num_entries; } ;
typedef  TYPE_1__ zend_accel_hash ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void zend_accel_hash_clean(zend_accel_hash *accel_hash)
{
	accel_hash->num_entries = 0;
	accel_hash->num_direct_entries = 0;
	memset(accel_hash->hash_table, 0, sizeof(zend_accel_hash_entry *)*accel_hash->max_num_entries);
}