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
typedef  int /*<<< orphan*/  uint32_t ;
struct spw303v_tag {int /*<<< orphan*/  headerCRC; int /*<<< orphan*/  imageCRC; int /*<<< orphan*/  certf1Address; int /*<<< orphan*/  signiture_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGETAG_CRC_START ; 
 int /*<<< orphan*/ * IMAGETAG_MAGIC1_TCOM ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,void*,int) ; 
 void* fake_data ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 

void fix_header(void *buf)
{
	struct spw303v_tag *tag = buf;
	uint32_t crc;
	/* Replace signature with custom t-com one */
	memset(tag->signiture_1, 0, 20);
	memcpy(tag->signiture_1, IMAGETAG_MAGIC1_TCOM, strlen(IMAGETAG_MAGIC1_TCOM));

	/* Clear cert fields to remove information_* data */
	memset(tag->certf1Address, 0, 74);

	/* replace image crc with modified one */
	crc = ntohl(*((uint32_t *)&tag->imageCRC));

	crc = htonl(crc32(crc, fake_data, 64));

	memcpy(tag->imageCRC, &crc, 4);

	/* Update tag crc */
	crc = htonl(crc32(IMAGETAG_CRC_START, buf, 236));
	memcpy(tag->headerCRC, &crc, 4);
}