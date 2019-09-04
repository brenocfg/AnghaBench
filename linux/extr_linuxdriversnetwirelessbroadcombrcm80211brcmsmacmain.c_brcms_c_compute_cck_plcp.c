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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_cck_plcp_set (struct brcms_c_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rspec2rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_compute_cck_plcp(struct brcms_c_info *wlc, u32 rspec,
				 uint length, u8 *plcp)
{
	int rate = rspec2rate(rspec);

	brcms_c_cck_plcp_set(wlc, rate, length, plcp);
}