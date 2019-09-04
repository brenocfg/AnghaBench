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
struct bm_portal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_REG_SCN (int) ; 
 int /*<<< orphan*/  bm_out (struct bm_portal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bm_isr_bscn_disable(struct bm_portal *portal)
{
	bm_out(portal, BM_REG_SCN(0), 0);
	bm_out(portal, BM_REG_SCN(1), 0);
}