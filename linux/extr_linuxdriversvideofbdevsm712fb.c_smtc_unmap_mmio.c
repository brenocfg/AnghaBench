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
struct smtcfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * smtc_regbaseaddress ; 

__attribute__((used)) static void smtc_unmap_mmio(struct smtcfb_info *sfb)
{
	if (sfb && smtc_regbaseaddress)
		smtc_regbaseaddress = NULL;
}