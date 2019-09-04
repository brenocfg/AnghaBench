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
 unsigned char ANT_A ; 
 unsigned char ANT_B ; 
 unsigned char ANT_DIVERSITY ; 
 int /*<<< orphan*/  BBbReadEmbedded (struct vnt_private*,int,unsigned char*) ; 
 int /*<<< orphan*/  BBbWriteEmbedded (struct vnt_private*,int,unsigned char) ; 

void
BBvSetTxAntennaMode(struct vnt_private *priv, unsigned char byAntennaMode)
{
	unsigned char byBBTxConf;

	BBbReadEmbedded(priv, 0x09, &byBBTxConf); /* CR09 */
	if (byAntennaMode == ANT_DIVERSITY) {
		/* bit 1 is diversity */
		byBBTxConf |= 0x02;
	} else if (byAntennaMode == ANT_A) {
		/* bit 2 is ANTSEL */
		byBBTxConf &= 0xF9; /* 1111 1001 */
	} else if (byAntennaMode == ANT_B) {
		byBBTxConf &= 0xFD; /* 1111 1101 */
		byBBTxConf |= 0x04;
	}
	BBbWriteEmbedded(priv, 0x09, byBBTxConf); /* CR09 */
}