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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  crc_t10dif_update (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

__u16 crc_t10dif(const unsigned char *buffer, size_t len)
{
	return crc_t10dif_update(0, buffer, len);
}