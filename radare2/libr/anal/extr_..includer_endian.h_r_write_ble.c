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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */
 int /*<<< orphan*/  r_write_ble16 (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_write_ble24 (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_write_ble32 (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_write_ble64 (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void r_write_ble(void *dst, ut64 val, bool big_endian, int size) {
	switch (size) {
	case 8:
		((ut8*)dst)[0] = (ut8) val;
		break;
	case 16:
		r_write_ble16 (dst, (ut16) val, big_endian);
		break;
	case 24:
		r_write_ble24 (dst, (ut32) val, big_endian);
		break;
	case 32:
		r_write_ble32 (dst, (ut32) val, big_endian);
		break;
	case 64:
		r_write_ble64 (dst, val, big_endian);
		break;
	default:
		break;
	}
}