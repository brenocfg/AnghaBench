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
typedef  int /*<<< orphan*/  ut16 ;
typedef  int /*<<< orphan*/  uint16_t ;
struct instruction {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline ut16 i2ut16(struct instruction *in) {
	return *((uint16_t*)in);
}