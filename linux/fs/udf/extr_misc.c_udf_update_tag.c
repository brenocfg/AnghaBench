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
struct tag {int /*<<< orphan*/  tagChecksum; void* descCRC; void* descCRCLength; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 
 int crc_itu_t (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  udf_tag_checksum (struct tag*) ; 

void udf_update_tag(char *data, int length)
{
	struct tag *tptr = (struct tag *)data;
	length -= sizeof(struct tag);

	tptr->descCRCLength = cpu_to_le16(length);
	tptr->descCRC = cpu_to_le16(crc_itu_t(0, data + sizeof(struct tag), length));
	tptr->tagChecksum = udf_tag_checksum(tptr);
}