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
struct sw842_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2_BITS ; 
 int /*<<< orphan*/  I2_FIFO_SIZE ; 
 int /*<<< orphan*/  I4_BITS ; 
 int /*<<< orphan*/  I4_FIFO_SIZE ; 
 int /*<<< orphan*/  I8_BITS ; 
 int /*<<< orphan*/  I8_FIFO_SIZE ; 
 int __do_index (struct sw842_param*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_index(struct sw842_param *p, u8 n)
{
	switch (n) {
	case 2:
		return __do_index(p, 2, I2_BITS, I2_FIFO_SIZE);
	case 4:
		return __do_index(p, 4, I4_BITS, I4_FIFO_SIZE);
	case 8:
		return __do_index(p, 8, I8_BITS, I8_FIFO_SIZE);
	default:
		return -EINVAL;
	}
}