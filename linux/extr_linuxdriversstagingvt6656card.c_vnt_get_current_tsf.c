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
typedef  int /*<<< orphan*/  u64 ;
struct vnt_private {int /*<<< orphan*/  current_tsf; } ;

/* Variables and functions */

bool vnt_get_current_tsf(struct vnt_private *priv, u64 *current_tsf)
{
	*current_tsf = priv->current_tsf;

	return true;
}