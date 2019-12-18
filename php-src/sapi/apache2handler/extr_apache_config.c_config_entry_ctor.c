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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  php_dir_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void config_entry_ctor(zval *zv)
{
	php_dir_entry *pe = (php_dir_entry*)Z_PTR_P(zv);
	php_dir_entry *npe = malloc(sizeof(php_dir_entry));

	memcpy(npe, pe, sizeof(php_dir_entry));
	ZVAL_PTR(zv, npe);
}