#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  nvec; } ;

/* Variables and functions */
 unsigned char AUTO_RECEIVE_N ; 
 unsigned char NVEC_PS2 ; 
 unsigned char PACKET_SIZE ; 
 int nvec_write_async (int /*<<< orphan*/ ,unsigned char*,int) ; 
 TYPE_1__ ps2_dev ; 

__attribute__((used)) static int ps2_startstreaming(struct serio *ser_dev)
{
	unsigned char buf[] = { NVEC_PS2, AUTO_RECEIVE_N, PACKET_SIZE };

	return nvec_write_async(ps2_dev.nvec, buf, sizeof(buf));
}