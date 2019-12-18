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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * memcpy (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * xdr_encode_u32 (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static __be32 *xdr_encode_string(__be32 *bp, const char *p, unsigned int len)
{
	bp = xdr_encode_u32(bp, len);
	bp = memcpy(bp, p, len);
	if (len & 3) {
		unsigned int pad = 4 - (len & 3);

		memset((u8 *)bp + len, 0, pad);
		len += pad;
	}

	return bp + len / sizeof(__be32);
}