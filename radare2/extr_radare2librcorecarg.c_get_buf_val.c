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
 scalar_t__ r_read_ble32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_read_ble64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ut64 get_buf_val(ut8 *buf, int endian, int width) {
	return (width == 8)? r_read_ble64 (buf, endian) : (ut64) r_read_ble32 (buf,endian);
}