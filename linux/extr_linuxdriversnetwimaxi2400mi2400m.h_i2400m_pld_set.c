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
struct i2400m_pld {int /*<<< orphan*/  val; } ;
typedef  enum i2400m_pt { ____Placeholder_i2400m_pt } i2400m_pt ;

/* Variables and functions */
 size_t I2400M_PLD_SIZE_MASK ; 
 int I2400M_PLD_TYPE_MASK ; 
 int I2400M_PLD_TYPE_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline
void i2400m_pld_set(struct i2400m_pld *pld, size_t size,
		    enum i2400m_pt type)
{
	pld->val = cpu_to_le32(
		((type << I2400M_PLD_TYPE_SHIFT) & I2400M_PLD_TYPE_MASK)
		|  (size & I2400M_PLD_SIZE_MASK));
}