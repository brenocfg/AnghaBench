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
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_EEE_100TX ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  r8152_eee_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8152_mmd_write (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8152b_enable_eee(struct r8152 *tp)
{
	r8152_eee_en(tp, true);
	r8152_mmd_write(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, MDIO_EEE_100TX);
}