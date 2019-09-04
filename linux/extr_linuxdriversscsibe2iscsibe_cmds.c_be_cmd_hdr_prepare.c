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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct be_cmd_req_hdr {int /*<<< orphan*/  timeout; int /*<<< orphan*/  request_length; void* subsystem; void* opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_FW_MBX_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

void be_cmd_hdr_prepare(struct be_cmd_req_hdr *req_hdr,
			u8 subsystem, u8 opcode, u32 cmd_len)
{
	req_hdr->opcode = opcode;
	req_hdr->subsystem = subsystem;
	req_hdr->request_length = cpu_to_le32(cmd_len - sizeof(*req_hdr));
	req_hdr->timeout = BEISCSI_FW_MBX_TIMEOUT;
}