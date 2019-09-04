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
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  MYSQLND_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  ps_fetch_from_1_to_8_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,unsigned int const,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static void
ps_fetch_int16(zval * zv, const MYSQLND_FIELD * const field, const unsigned int pack_len, const zend_uchar ** row)
{
	ps_fetch_from_1_to_8_bytes(zv, field, pack_len, row, 2);
}