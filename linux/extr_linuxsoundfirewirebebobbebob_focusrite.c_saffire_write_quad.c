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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_bebob {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ SAFFIRE_ADDRESS_BASE ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
saffire_write_quad(struct snd_bebob *bebob, u64 offset, u32 value)
{
	__be32 data = cpu_to_be32(value);

	return snd_fw_transaction(bebob->unit, TCODE_WRITE_QUADLET_REQUEST,
				  SAFFIRE_ADDRESS_BASE + offset,
				  &data, sizeof(__be32), 0);
}