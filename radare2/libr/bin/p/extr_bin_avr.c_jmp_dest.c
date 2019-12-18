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
typedef  int ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_read8_at (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ut64 jmp_dest(RBuffer* b, ut64 addr) {
	return (r_buf_read8_at (b, addr + 2) + (r_buf_read8_at (b, addr + 3) << 8)) * 2;
}