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
struct fw_cmd_hdr {int /*<<< orphan*/  lo; } ;
struct csio_mb {scalar_t__ mb; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 int FW_CMD_RETVAL_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

enum fw_retval
csio_mb_fw_retval(struct csio_mb *mbp)
{
	struct fw_cmd_hdr *hdr;

	hdr = (struct fw_cmd_hdr *)(mbp->mb);

	return FW_CMD_RETVAL_G(ntohl(hdr->lo));
}