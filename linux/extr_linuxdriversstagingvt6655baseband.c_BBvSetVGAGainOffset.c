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
struct vnt_private {unsigned char* abyBBVGA; unsigned char byBBVGACurrent; scalar_t__ bShortSlotTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBbReadEmbedded (struct vnt_private*,int,unsigned char*) ; 
 int /*<<< orphan*/  BBbWriteEmbedded (struct vnt_private*,int,unsigned char) ; 

void BBvSetVGAGainOffset(struct vnt_private *priv, unsigned char byData)
{
	unsigned char byBBRxConf = 0;

	BBbWriteEmbedded(priv, 0xE7, byData);

	BBbReadEmbedded(priv, 0x0A, &byBBRxConf); /* CR10 */
	/* patch for 3253B0 Baseband with Cardbus module */
	if (byData == priv->abyBBVGA[0])
		byBBRxConf |= 0x20; /* 0010 0000 */
	else if (priv->bShortSlotTime)
		byBBRxConf &= 0xDF; /* 1101 1111 */
	else
		byBBRxConf |= 0x20; /* 0010 0000 */
	priv->byBBVGACurrent = byData;
	BBbWriteEmbedded(priv, 0x0A, byBBRxConf); /* CR10 */
}