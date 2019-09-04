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
typedef  int uint16_t ;
struct lbs_private {scalar_t__ mesh_channel; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t lbs_mesh_get_channel(struct lbs_private *priv)
{
	return priv->mesh_channel ?: 1;
}