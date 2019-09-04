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
struct vnt_private {scalar_t__ byBBType; } ;

/* Variables and functions */
 scalar_t__ BB_TYPE_11A ; 
 scalar_t__ BB_TYPE_11B ; 
 scalar_t__ CARDbIsOFDMinBasicRate (void*) ; 
 unsigned char PK_TYPE_11GA ; 
 unsigned char PK_TYPE_11GB ; 

unsigned char CARDbyGetPktType(struct vnt_private *priv)
{
	if (priv->byBBType == BB_TYPE_11A || priv->byBBType == BB_TYPE_11B)
		return (unsigned char)priv->byBBType;
	else if (CARDbIsOFDMinBasicRate((void *)priv))
		return PK_TYPE_11GA;
	else
		return PK_TYPE_11GB;
}