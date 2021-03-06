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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct intel8x0 {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 

__attribute__((used)) static inline u16 iagetword(struct intel8x0 *chip, u32 offset)
{
	return ioread16(chip->addr + offset);
}