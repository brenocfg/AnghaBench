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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  scalar_t__ zend_uchar ;
typedef  scalar_t__ const uint64_t ;

/* Variables and functions */
 scalar_t__ L64 (int) ; 
 int /*<<< orphan*/  int2store (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/  int3store (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int8store (scalar_t__*,scalar_t__ const) ; 

zend_uchar *
php_mysqlnd_net_store_length(zend_uchar *packet, const uint64_t length)
{
	if (length < (uint64_t) L64(251)) {
		*packet = (zend_uchar) length;
		return packet + 1;
	}

	if (length < (uint64_t) L64(65536)) {
		*packet++ = 252;
		int2store(packet,(unsigned int) length);
		return packet + 2;
	}

	if (length < (uint64_t) L64(16777216)) {
		*packet++ = 253;
		int3store(packet,(zend_ulong) length);
		return packet + 3;
	}
	*packet++ = 254;
	int8store(packet, length);
	return packet + 8;
}