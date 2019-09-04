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
typedef  size_t u16 ;
struct vnt_private {int byPreambleType; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t MAX_RATE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** wTimeStampOff ; 

__attribute__((used)) static __le16 vnt_time_stamp_off(struct vnt_private *priv, u16 rate)
{
	return cpu_to_le16(wTimeStampOff[priv->byPreambleType % 2]
							[rate % MAX_RATE]);
}