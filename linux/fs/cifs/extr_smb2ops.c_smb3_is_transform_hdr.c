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
struct smb2_transform_hdr {scalar_t__ ProtocolId; } ;

/* Variables and functions */
 scalar_t__ SMB2_TRANSFORM_PROTO_NUM ; 

__attribute__((used)) static int
smb3_is_transform_hdr(void *buf)
{
	struct smb2_transform_hdr *trhdr = buf;

	return trhdr->ProtocolId == SMB2_TRANSFORM_PROTO_NUM;
}