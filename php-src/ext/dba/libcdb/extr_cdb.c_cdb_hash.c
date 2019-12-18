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
typedef  int uint32 ;

/* Variables and functions */
 int CDB_HASHSTART ; 

uint32 cdb_hash(char *buf, unsigned int len)
{
	uint32 h;
	const unsigned char * b = (unsigned char *)buf;

	h = CDB_HASHSTART;
	while (len--) {
		h = ( h + (h << 5)) ^ (*b++);
	}
	return h;
}