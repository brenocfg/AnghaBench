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
typedef  int u8 ;
struct snic_fw_req {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
snic_color_enc(struct snic_fw_req *req, u8 color)
{
	u8 *c = ((u8 *) req) + sizeof(struct snic_fw_req) - 1;

	if (color)
		*c |= 0x80;
	else
		*c &= ~0x80;
}