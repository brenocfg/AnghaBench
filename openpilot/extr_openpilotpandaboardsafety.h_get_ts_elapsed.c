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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t get_ts_elapsed(uint32_t ts, uint32_t ts_last) {
  return ts > ts_last ? ts - ts_last : (0xFFFFFFFF - ts_last) + 1 + ts;
}