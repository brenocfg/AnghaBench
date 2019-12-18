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

/* Variables and functions */

void set_checksum(unsigned char*img, unsigned short sum)
{
  img[0x3dfffc] = sum & 0xff;
  img[0x3dfffd] = (sum>>8) & 0xff;
}