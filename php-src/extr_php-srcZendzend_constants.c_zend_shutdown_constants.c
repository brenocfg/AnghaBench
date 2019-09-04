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
 int SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_constants ; 
 int /*<<< orphan*/  zend_hash_destroy (int /*<<< orphan*/ ) ; 

int zend_shutdown_constants(void)
{
	zend_hash_destroy(EG(zend_constants));
	free(EG(zend_constants));
	return SUCCESS;
}