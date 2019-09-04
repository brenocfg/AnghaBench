#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; int /*<<< orphan*/  result; TYPE_1__* request; } ;
struct TYPE_4__ {int /*<<< orphan*/  sdev_gendev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 char const* driver_byte (int /*<<< orphan*/ ) ; 
 char const* host_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_name (struct scsi_cmnd const*) ; 
 scalar_t__ scnprintf (char*,size_t,char*,...) ; 
 char* scsi_driverbyte_string (int /*<<< orphan*/ ) ; 
 char* scsi_hostbyte_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_log_release_buffer (char*) ; 
 char* scsi_log_reserve_buffer (size_t*) ; 
 char* scsi_mlreturn_string (int) ; 
 size_t sdev_format_header (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void scsi_print_result(const struct scsi_cmnd *cmd, const char *msg,
		       int disposition)
{
	char *logbuf;
	size_t off, logbuf_len;
	const char *mlret_string = scsi_mlreturn_string(disposition);
	const char *hb_string = scsi_hostbyte_string(cmd->result);
	const char *db_string = scsi_driverbyte_string(cmd->result);

	logbuf = scsi_log_reserve_buffer(&logbuf_len);
	if (!logbuf)
		return;

	off = sdev_format_header(logbuf, logbuf_len,
				 scmd_name(cmd), cmd->request->tag);

	if (off >= logbuf_len)
		goto out_printk;

	if (msg) {
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "%s: ", msg);
		if (WARN_ON(off >= logbuf_len))
			goto out_printk;
	}
	if (mlret_string)
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "%s ", mlret_string);
	else
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "UNKNOWN(0x%02x) ", disposition);
	if (WARN_ON(off >= logbuf_len))
		goto out_printk;

	off += scnprintf(logbuf + off, logbuf_len - off, "Result: ");
	if (WARN_ON(off >= logbuf_len))
		goto out_printk;

	if (hb_string)
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "hostbyte=%s ", hb_string);
	else
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "hostbyte=0x%02x ", host_byte(cmd->result));
	if (WARN_ON(off >= logbuf_len))
		goto out_printk;

	if (db_string)
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "driverbyte=%s", db_string);
	else
		off += scnprintf(logbuf + off, logbuf_len - off,
				 "driverbyte=0x%02x", driver_byte(cmd->result));
out_printk:
	dev_printk(KERN_INFO, &cmd->device->sdev_gendev, "%s", logbuf);
	scsi_log_release_buffer(logbuf);
}