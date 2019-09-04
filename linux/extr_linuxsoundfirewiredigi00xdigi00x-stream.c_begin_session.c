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
typedef  int u32 ;
struct snd_dg00x {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ DG00X_ADDR_BASE ; 
 scalar_t__ DG00X_OFFSET_STREAMING_SET ; 
 scalar_t__ DG00X_OFFSET_STREAMING_STATE ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  finish_session (struct snd_dg00x*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int begin_session(struct snd_dg00x *dg00x)
{
	__be32 data;
	u32 curr;
	int err;

	err = snd_fw_transaction(dg00x->unit, TCODE_READ_QUADLET_REQUEST,
				 DG00X_ADDR_BASE + DG00X_OFFSET_STREAMING_STATE,
				 &data, sizeof(data), 0);
	if (err < 0)
		goto error;
	curr = be32_to_cpu(data);

	if (curr == 0)
		curr = 2;

	curr--;
	while (curr > 0) {
		data = cpu_to_be32(curr);
		err = snd_fw_transaction(dg00x->unit,
					 TCODE_WRITE_QUADLET_REQUEST,
					 DG00X_ADDR_BASE +
					 DG00X_OFFSET_STREAMING_SET,
					 &data, sizeof(data), 0);
		if (err < 0)
			goto error;

		msleep(20);
		curr--;
	}

	return 0;
error:
	finish_session(dg00x);
	return err;
}