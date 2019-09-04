#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_2__ {int is_writeable; int /*<<< orphan*/  is_data; } ;
typedef  TYPE_1__ phar_archive_data ;

/* Variables and functions */
 int ZEND_HASH_APPLY_KEEP ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_set_writeable_bit(zval *zv, void *argument) /* {{{ */
{
	zend_bool keep = *(zend_bool *)argument;
	phar_archive_data *phar = (phar_archive_data *)Z_PTR_P(zv);

	if (!phar->is_data) {
		phar->is_writeable = !keep;
	}

	return ZEND_HASH_APPLY_KEEP;
}