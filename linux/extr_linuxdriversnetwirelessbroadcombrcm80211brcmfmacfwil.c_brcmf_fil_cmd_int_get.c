#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_if {int /*<<< orphan*/  ifidx; TYPE_1__* drvr; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  data_le ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  proto_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIL ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fil_cmd_data (struct brcmf_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

s32
brcmf_fil_cmd_int_get(struct brcmf_if *ifp, u32 cmd, u32 *data)
{
	s32 err;
	__le32 data_le = cpu_to_le32(*data);

	mutex_lock(&ifp->drvr->proto_block);
	err = brcmf_fil_cmd_data(ifp, cmd, &data_le, sizeof(data_le), false);
	mutex_unlock(&ifp->drvr->proto_block);
	*data = le32_to_cpu(data_le);
	brcmf_dbg(FIL, "ifidx=%d, cmd=%d, value=%d\n", ifp->ifidx, cmd, *data);

	return err;
}