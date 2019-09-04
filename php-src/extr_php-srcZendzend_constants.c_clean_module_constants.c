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

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_module_constant ; 
 int /*<<< orphan*/  zend_constants ; 
 int /*<<< orphan*/  zend_hash_apply_with_argument (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void clean_module_constants(int module_number)
{
	zend_hash_apply_with_argument(EG(zend_constants), clean_module_constant, (void *) &module_number);
}