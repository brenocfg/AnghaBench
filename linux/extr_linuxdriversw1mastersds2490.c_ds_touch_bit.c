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
typedef  scalar_t__ u8 ;
struct ds_status {int dummy; } ;
struct ds_device {int dummy; } ;

/* Variables and functions */
 int COMM_BIT_IO ; 
 int COMM_D ; 
 int COMM_IM ; 
 int ds_recv_data (struct ds_device*,scalar_t__*,int) ; 
 int ds_send_control (struct ds_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_wait_status (struct ds_device*,struct ds_status*) ; 

__attribute__((used)) static int ds_touch_bit(struct ds_device *dev, u8 bit, u8 *tbit)
{
	int err;
	struct ds_status st;

	err = ds_send_control(dev, COMM_BIT_IO | COMM_IM | (bit ? COMM_D : 0),
		0);
	if (err)
		return err;

	ds_wait_status(dev, &st);

	err = ds_recv_data(dev, tbit, sizeof(*tbit));
	if (err < 0)
		return err;

	return 0;
}