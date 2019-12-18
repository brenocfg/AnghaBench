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
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
saffire_read_quad(struct snd_bebob *bebob, u64 offset, u32 *value)
{
	int err;
	__be32 tmp;

	err = snd_fw_transaction(bebob->unit, TCODE_READ_QUADLET_REQUEST,
				 SAFFIRE_ADDRESS_BASE + offset,
				 &tmp, sizeof(__be32), 0);
	if (err < 0)
		goto end;

	*value = be32_to_cpu(tmp);
end:
	return err;
}