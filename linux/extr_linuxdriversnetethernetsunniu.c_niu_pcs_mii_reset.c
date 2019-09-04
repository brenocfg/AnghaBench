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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCS_MII_CTL ; 
 int PCS_MII_CTL_RST ; 
 int nr64_pcs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_pcs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void niu_pcs_mii_reset(struct niu *np)
{
	int limit = 1000;
	u64 val = nr64_pcs(PCS_MII_CTL);
	val |= PCS_MII_CTL_RST;
	nw64_pcs(PCS_MII_CTL, val);
	while ((--limit >= 0) && (val & PCS_MII_CTL_RST)) {
		udelay(100);
		val = nr64_pcs(PCS_MII_CTL);
	}
}