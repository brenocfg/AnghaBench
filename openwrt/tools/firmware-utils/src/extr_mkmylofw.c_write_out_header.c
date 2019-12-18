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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mylo_fw_header {void* flags; void* fwlo; void* fwhi; void* rev; void* sdid; void* svid; void* did; void* vid; void* crc; void* magic; } ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  fwlo; int /*<<< orphan*/  fwhi; int /*<<< orphan*/  rev; int /*<<< orphan*/  sdid; int /*<<< orphan*/  svid; int /*<<< orphan*/  did; int /*<<< orphan*/  vid; int /*<<< orphan*/  crc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* HOST_TO_LE16 (int /*<<< orphan*/ ) ; 
 void* HOST_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYLO_MAGIC_FIRMWARE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errmsg (int,char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fw_header ; 
 int /*<<< orphan*/  memset (struct mylo_fw_header*,int /*<<< orphan*/ ,int) ; 
 int write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
write_out_header(FILE *outfile, uint32_t *crc)
{
	struct mylo_fw_header hdr;

	memset(&hdr, 0, sizeof(hdr));

	hdr.magic = HOST_TO_LE32(MYLO_MAGIC_FIRMWARE);
	hdr.crc = HOST_TO_LE32(fw_header.crc);
	hdr.vid = HOST_TO_LE16(fw_header.vid);
	hdr.did = HOST_TO_LE16(fw_header.did);
	hdr.svid = HOST_TO_LE16(fw_header.svid);
	hdr.sdid = HOST_TO_LE16(fw_header.sdid);
	hdr.rev = HOST_TO_LE32(fw_header.rev);
	hdr.fwhi = HOST_TO_LE32(fw_header.fwhi);
	hdr.fwlo = HOST_TO_LE32(fw_header.fwlo);
	hdr.flags = HOST_TO_LE32(fw_header.flags);

	if (fseek(outfile, 0, SEEK_SET) != 0) {
		errmsg(1,"fseek failed on output file");
		return -1;
	}

	return write_out_data(outfile, (uint8_t *)&hdr, sizeof(hdr), crc);
}