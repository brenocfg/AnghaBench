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
typedef  scalar_t__ vlen ;
typedef  scalar_t__ ut8 ;
typedef  scalar_t__ ut32 ;

/* Variables and functions */
 scalar_t__ SDB_MAX_KEY ; 
 scalar_t__ SDB_MAX_VALUE ; 

__attribute__((used)) static int pack_kvlen(ut8 *buf, ut32 klen, ut32 vlen) {
	if (klen > SDB_MAX_KEY) {
		return 0; // 0xff = 254 chars+trailing zero
	}
	if (vlen >= SDB_MAX_VALUE) {
		return 0;
	}
	buf[0] = (ut8)klen;
	buf[1] = (ut8)((vlen      ) & 0xff);
	buf[2] = (ut8)((vlen >> 8 ) & 0xff);
	buf[3] = (ut8)((vlen >> 16) & 0xff);
	return 1;
}