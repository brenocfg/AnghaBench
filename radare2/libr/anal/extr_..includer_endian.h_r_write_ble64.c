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
 int /*<<< orphan*/  r_write_be64 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_write_le64 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void r_write_ble64(void *dest, ut64 val, bool big_endian) {
	big_endian? r_write_be64 (dest, val): r_write_le64 (dest, val);
}