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

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ naa3_comp_a ; 
 int /*<<< orphan*/  put_unaligned_be64 (scalar_t__,unsigned char*) ; 

__attribute__((used)) static int inquiry_vpd_88(unsigned char *arr, int target_dev_id)
{
	int num = 0;
	int port_a, port_b;

	port_a = target_dev_id + 1;
	port_b = port_a + 1;
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	arr[num++] = 0x1;	/* relative port 1 (primary) */
	memset(arr + num, 0, 6);
	num += 6;
	arr[num++] = 0x0;
	arr[num++] = 12;	/* length tp descriptor */
	/* naa-5 target port identifier (A) */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* PIV=1, target port, NAA */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x8;	/* length */
	put_unaligned_be64(naa3_comp_a + port_a, arr + num);
	num += 8;
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x0;
	arr[num++] = 0x2;	/* relative port 2 (secondary) */
	memset(arr + num, 0, 6);
	num += 6;
	arr[num++] = 0x0;
	arr[num++] = 12;	/* length tp descriptor */
	/* naa-5 target port identifier (B) */
	arr[num++] = 0x61;	/* proto=sas, binary */
	arr[num++] = 0x93;	/* PIV=1, target port, NAA */
	arr[num++] = 0x0;	/* reserved */
	arr[num++] = 0x8;	/* length */
	put_unaligned_be64(naa3_comp_a + port_b, arr + num);
	num += 8;

	return num;
}