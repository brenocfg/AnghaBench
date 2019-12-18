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
 int mg_hexdump_n (void const*,int,char*,int,int /*<<< orphan*/ ) ; 

int mg_hexdump(const void *buf, int len, char *dst, int dst_len) {
  return mg_hexdump_n(buf, len, dst, dst_len, 0);
}