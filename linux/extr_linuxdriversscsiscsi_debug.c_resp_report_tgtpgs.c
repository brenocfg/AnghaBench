#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdebug_dev_info {int channel; TYPE_2__* sdbg_host; } ;
struct scsi_cmnd {unsigned char* cmnd; } ;
struct TYPE_4__ {TYPE_1__* shost; } ;
struct TYPE_3__ {int host_no; } ;

/* Variables and functions */
 int DID_REQUEUE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SDEBUG_MAX_TGTPGS_ARR_SZ ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int) ; 
 int get_unaligned_be32 (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,unsigned char*) ; 
 scalar_t__ sdebug_vpd_use_hostno ; 

__attribute__((used)) static int resp_report_tgtpgs(struct scsi_cmnd *scp,
			      struct sdebug_dev_info *devip)
{
	unsigned char *cmd = scp->cmnd;
	unsigned char *arr;
	int host_no = devip->sdbg_host->shost->host_no;
	int n, ret, alen, rlen;
	int port_group_a, port_group_b, port_a, port_b;

	alen = get_unaligned_be32(cmd + 6);
	arr = kzalloc(SDEBUG_MAX_TGTPGS_ARR_SZ, GFP_ATOMIC);
	if (! arr)
		return DID_REQUEUE << 16;
	/*
	 * EVPD page 0x88 states we have two ports, one
	 * real and a fake port with no device connected.
	 * So we create two port groups with one port each
	 * and set the group with port B to unavailable.
	 */
	port_a = 0x1; /* relative port A */
	port_b = 0x2; /* relative port B */
	port_group_a = (((host_no + 1) & 0x7f) << 8) +
			(devip->channel & 0x7f);
	port_group_b = (((host_no + 1) & 0x7f) << 8) +
			(devip->channel & 0x7f) + 0x80;

	/*
	 * The asymmetric access state is cycled according to the host_id.
	 */
	n = 4;
	if (sdebug_vpd_use_hostno == 0) {
		arr[n++] = host_no % 3; /* Asymm access state */
		arr[n++] = 0x0F; /* claim: all states are supported */
	} else {
		arr[n++] = 0x0; /* Active/Optimized path */
		arr[n++] = 0x01; /* only support active/optimized paths */
	}
	put_unaligned_be16(port_group_a, arr + n);
	n += 2;
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Status code */
	arr[n++] = 0;    /* Vendor unique */
	arr[n++] = 0x1;  /* One port per group */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Reserved */
	put_unaligned_be16(port_a, arr + n);
	n += 2;
	arr[n++] = 3;    /* Port unavailable */
	arr[n++] = 0x08; /* claim: only unavailalbe paths are supported */
	put_unaligned_be16(port_group_b, arr + n);
	n += 2;
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Status code */
	arr[n++] = 0;    /* Vendor unique */
	arr[n++] = 0x1;  /* One port per group */
	arr[n++] = 0;    /* Reserved */
	arr[n++] = 0;    /* Reserved */
	put_unaligned_be16(port_b, arr + n);
	n += 2;

	rlen = n - 4;
	put_unaligned_be32(rlen, arr + 0);

	/*
	 * Return the smallest value of either
	 * - The allocated length
	 * - The constructed command length
	 * - The maximum array size
	 */
	rlen = min(alen,n);
	ret = fill_from_dev_buffer(scp, arr,
				   min(rlen, SDEBUG_MAX_TGTPGS_ARR_SZ));
	kfree(arr);
	return ret;
}