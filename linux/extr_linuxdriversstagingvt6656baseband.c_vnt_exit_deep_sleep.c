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
 int /*<<< orphan*/  MESSAGE_REQUEST_BBREG ; 
 int /*<<< orphan*/  vnt_control_out_u8 (struct vnt_private*,int /*<<< orphan*/ ,int,int) ; 

void vnt_exit_deep_sleep(struct vnt_private *priv)
{
	vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0x0c, 0x00);/* CR12 */
	vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0x0d, 0x01);/* CR13 */
}