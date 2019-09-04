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
 int /*<<< orphan*/  BBbWriteEmbedded (struct vnt_private*,int,int) ; 

void
BBvExitDeepSleep(struct vnt_private *priv, unsigned char byLocalID)
{
	BBbWriteEmbedded(priv, 0x0C, 0x00); /* CR12 */
	BBbWriteEmbedded(priv, 0x0D, 0x01); /* CR13 */
}