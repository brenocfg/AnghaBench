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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  bytesToHex (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  calculateDigestFromBuffer (void const*,size_t,int /*<<< orphan*/ *) ; 

bool
pg_md5_hash(const void *buff, size_t len, char *hexsum)
{
	uint8		sum[16];

	if (!calculateDigestFromBuffer(buff, len, sum))
		return false;

	bytesToHex(sum, hexsum);
	return true;
}