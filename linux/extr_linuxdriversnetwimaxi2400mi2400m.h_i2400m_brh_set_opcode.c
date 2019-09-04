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
struct i2400m_bootrom_header {int /*<<< orphan*/  command; } ;
typedef  enum i2400m_brh_opcode { ____Placeholder_i2400m_brh_opcode } i2400m_brh_opcode ;

/* Variables and functions */
 int I2400M_BRH_OPCODE_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void i2400m_brh_set_opcode(struct i2400m_bootrom_header *hdr,
			   enum i2400m_brh_opcode opcode)
{
	hdr->command = cpu_to_le32(
		(le32_to_cpu(hdr->command) & ~I2400M_BRH_OPCODE_MASK)
		| (opcode & I2400M_BRH_OPCODE_MASK));
}