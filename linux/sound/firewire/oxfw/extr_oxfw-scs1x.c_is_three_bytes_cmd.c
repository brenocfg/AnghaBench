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

/* Variables and functions */

__attribute__((used)) static bool is_three_bytes_cmd(u8 status)
{
	return (status >= 0x80 && status <= 0xbf) ||
	       (status >= 0xe0 && status <= 0xef) ||
	       status == 0xf2;
}