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
typedef  int /*<<< orphan*/  ut64 ;

/* Variables and functions */
 int /*<<< orphan*/  r_read_be64 (void const*) ; 
 int /*<<< orphan*/  r_read_le64 (void const*) ; 

__attribute__((used)) static inline ut64 r_read_ble64(const void *src, bool big_endian) {
	return big_endian? r_read_be64 (src): r_read_le64 (src);
}