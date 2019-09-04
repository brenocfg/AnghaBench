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
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBbReadEmbedded (struct vnt_private*,int,unsigned char*) ; 
 int /*<<< orphan*/  BBbWriteEmbedded (struct vnt_private*,int,unsigned char) ; 
 unsigned char BIT (int /*<<< orphan*/ ) ; 

void
BBvPowerSaveModeOFF(struct vnt_private *priv)
{
	unsigned char byOrgData;

	BBbReadEmbedded(priv, 0x0D, &byOrgData);
	byOrgData &= ~(BIT(0));
	BBbWriteEmbedded(priv, 0x0D, byOrgData);
}