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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_band {scalar_t__ bandtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  APHY_SIFS_TIME ; 
 int /*<<< orphan*/  BPHY_SIFS_TIME ; 
 scalar_t__ BRCM_BAND_5G ; 

__attribute__((used)) static u16 get_sifs(struct brcms_band *band)
{
	return band->bandtype == BRCM_BAND_5G ? APHY_SIFS_TIME :
				 BPHY_SIFS_TIME;
}