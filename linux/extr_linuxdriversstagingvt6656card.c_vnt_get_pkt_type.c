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
typedef  int /*<<< orphan*/  u8 ;
struct vnt_private {scalar_t__ bb_type; } ;

/* Variables and functions */
 scalar_t__ BB_TYPE_11A ; 
 scalar_t__ BB_TYPE_11B ; 
 int /*<<< orphan*/  PK_TYPE_11GA ; 
 int /*<<< orphan*/  PK_TYPE_11GB ; 
 scalar_t__ vnt_ofdm_min_rate (struct vnt_private*) ; 

u8 vnt_get_pkt_type(struct vnt_private *priv)
{
	if (priv->bb_type == BB_TYPE_11A || priv->bb_type == BB_TYPE_11B)
		return (u8)priv->bb_type;
	else if (vnt_ofdm_min_rate(priv))
		return PK_TYPE_11GA;
	return PK_TYPE_11GB;
}