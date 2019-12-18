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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct timestamp {int /*<<< orphan*/  typeAndTimezone; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
struct super_block {int dummy; } ;
struct primaryVolDesc {int /*<<< orphan*/  volSetIdent; int /*<<< orphan*/  volIdent; struct timestamp recordingDateAndTime; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {scalar_t__* s_volume_ident; int /*<<< orphan*/  s_record_time; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ TAG_IDENT_PVD ; 
 TYPE_1__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  udf_debug (char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  udf_disk_stamp_to_time (int /*<<< orphan*/ *,struct timestamp) ; 
 int udf_dstrCS0toChar (struct super_block*,scalar_t__*,int,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* udf_read_tagged (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int udf_load_pvoldesc(struct super_block *sb, sector_t block)
{
	struct primaryVolDesc *pvoldesc;
	uint8_t *outstr;
	struct buffer_head *bh;
	uint16_t ident;
	int ret = -ENOMEM;
	struct timestamp *ts;

	outstr = kmalloc(128, GFP_NOFS);
	if (!outstr)
		return -ENOMEM;

	bh = udf_read_tagged(sb, block, block, &ident);
	if (!bh) {
		ret = -EAGAIN;
		goto out2;
	}

	if (ident != TAG_IDENT_PVD) {
		ret = -EIO;
		goto out_bh;
	}

	pvoldesc = (struct primaryVolDesc *)bh->b_data;

	udf_disk_stamp_to_time(&UDF_SB(sb)->s_record_time,
			      pvoldesc->recordingDateAndTime);
	ts = &pvoldesc->recordingDateAndTime;
	udf_debug("recording time %04u/%02u/%02u %02u:%02u (%x)\n",
		  le16_to_cpu(ts->year), ts->month, ts->day, ts->hour,
		  ts->minute, le16_to_cpu(ts->typeAndTimezone));

	ret = udf_dstrCS0toChar(sb, outstr, 31, pvoldesc->volIdent, 32);
	if (ret < 0) {
		strcpy(UDF_SB(sb)->s_volume_ident, "InvalidName");
		pr_warn("incorrect volume identification, setting to "
			"'InvalidName'\n");
	} else {
		strncpy(UDF_SB(sb)->s_volume_ident, outstr, ret);
	}
	udf_debug("volIdent[] = '%s'\n", UDF_SB(sb)->s_volume_ident);

	ret = udf_dstrCS0toChar(sb, outstr, 127, pvoldesc->volSetIdent, 128);
	if (ret < 0) {
		ret = 0;
		goto out_bh;
	}
	outstr[ret] = 0;
	udf_debug("volSetIdent[] = '%s'\n", outstr);

	ret = 0;
out_bh:
	brelse(bh);
out2:
	kfree(outstr);
	return ret;
}