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
typedef  int /*<<< orphan*/  pdo_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdo_driver_hash ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int) ; 

pdo_driver_t *pdo_find_driver(const char *name, int namelen) /* {{{ */
{
	return zend_hash_str_find_ptr(&pdo_driver_hash, (char*)name, namelen);
}