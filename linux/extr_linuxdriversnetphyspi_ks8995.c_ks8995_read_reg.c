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
typedef  int /*<<< orphan*/  u8 ;
struct ks8995_switch {int dummy; } ;

/* Variables and functions */
 int ks8995_read (struct ks8995_switch*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ks8995_read_reg(struct ks8995_switch *ks, u8 addr, u8 *buf)
{
	return ks8995_read(ks, buf, addr, 1) != 1;
}