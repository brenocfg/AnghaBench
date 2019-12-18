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

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  r_read_ble16 (void const*,int) ; 
 int /*<<< orphan*/  r_read_ble32 (void const*,int) ; 
 int /*<<< orphan*/  r_read_ble64 (void const*,int) ; 

__attribute__((used)) static inline ut64 r_read_ble(const void *src, bool big_endian, int size) {
	switch (size) {
	case 8:
		return (ut64) ((const ut8*)src)[0];
	case 16:
		return r_read_ble16 (src, big_endian);
	case 32:
		return r_read_ble32 (src, big_endian);
	case 64:
		return r_read_ble64 (src, big_endian);
	default:
		return UT64_MAX;
	}
}