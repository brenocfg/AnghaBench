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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_if {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  data_le ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_fil_iovar_data_set (struct brcmf_if*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

s32
brcmf_fil_iovar_int_set(struct brcmf_if *ifp, char *name, u32 data)
{
	__le32 data_le = cpu_to_le32(data);

	return brcmf_fil_iovar_data_set(ifp, name, &data_le, sizeof(data_le));
}