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
typedef  int zend_uchar ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MYSQLND_NULL_LENGTH ; 
 int /*<<< orphan*/  uint2korr (int const*) ; 
 int /*<<< orphan*/  uint3korr (int const*) ; 
 int /*<<< orphan*/  uint8korr (int const*) ; 

uint64_t
php_mysqlnd_net_field_length_ll(const zend_uchar **packet)
{
	register const zend_uchar *p = (zend_uchar *)*packet;

	if (*p < 251) {
		(*packet)++;
		return (uint64_t) *p;
	}

	switch (*p) {
		case 251:
			(*packet)++;
			return (uint64_t) MYSQLND_NULL_LENGTH;
		case 252:
			(*packet) += 3;
			return (uint64_t) uint2korr(p + 1);
		case 253:
			(*packet) += 4;
			return (uint64_t) uint3korr(p + 1);
		default:
			(*packet) += 9;
			return (uint64_t) uint8korr(p + 1);
	}
}