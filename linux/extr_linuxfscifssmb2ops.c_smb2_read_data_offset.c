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
struct smb2_read_rsp {unsigned int DataOffset; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
smb2_read_data_offset(char *buf)
{
	struct smb2_read_rsp *rsp = (struct smb2_read_rsp *)buf;
	return rsp->DataOffset;
}