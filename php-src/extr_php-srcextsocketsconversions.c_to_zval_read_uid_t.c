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
typedef  int /*<<< orphan*/  zend_long ;
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  res_context ;
typedef  int /*<<< orphan*/  ival ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 

__attribute__((used)) static void to_zval_read_uid_t(const char *data, zval *zv, res_context *ctx)
{
	uid_t ival;
	memcpy(&ival, data, sizeof(ival));

	ZVAL_LONG(zv, (zend_long)ival);
}