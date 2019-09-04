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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 

__attribute__((used)) static void xdr_dump_bad(const __be32 *bp)
{
	__be32 x[4];
	int i;

	pr_notice("AFS XDR: Bad status record\n");
	for (i = 0; i < 5 * 4 * 4; i += 16) {
		memcpy(x, bp, 16);
		bp += 4;
		pr_notice("%03x: %08x %08x %08x %08x\n",
			  i, ntohl(x[0]), ntohl(x[1]), ntohl(x[2]), ntohl(x[3]));
	}

	memcpy(x, bp, 4);
	pr_notice("0x50: %08x\n", ntohl(x[0]));
}