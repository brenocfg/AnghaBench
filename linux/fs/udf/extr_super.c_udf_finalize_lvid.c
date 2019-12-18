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
struct timespec64 {int dummy; } ;
struct tag {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tagChecksum; int /*<<< orphan*/  descCRCLength; int /*<<< orphan*/  descCRC; } ;
struct logicalVolIntegrityDesc {TYPE_1__ descTag; int /*<<< orphan*/  recordingDateAndTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_itu_t (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_tag_checksum (TYPE_1__*) ; 
 int /*<<< orphan*/  udf_time_to_disk_stamp (int /*<<< orphan*/ *,struct timespec64) ; 

__attribute__((used)) static void udf_finalize_lvid(struct logicalVolIntegrityDesc *lvid)
{
	struct timespec64 ts;

	ktime_get_real_ts64(&ts);
	udf_time_to_disk_stamp(&lvid->recordingDateAndTime, ts);
	lvid->descTag.descCRC = cpu_to_le16(
		crc_itu_t(0, (char *)lvid + sizeof(struct tag),
			le16_to_cpu(lvid->descTag.descCRCLength)));
	lvid->descTag.tagChecksum = udf_tag_checksum(&lvid->descTag);
}