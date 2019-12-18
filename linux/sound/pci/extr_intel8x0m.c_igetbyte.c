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
typedef  scalar_t__ u32 ;
struct intel8x0m {scalar_t__ bmaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 

__attribute__((used)) static inline u8 igetbyte(struct intel8x0m *chip, u32 offset)
{
	return ioread8(chip->bmaddr + offset);
}