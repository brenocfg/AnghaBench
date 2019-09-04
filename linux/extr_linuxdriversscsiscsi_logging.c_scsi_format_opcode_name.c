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

/* Variables and functions */
 int VARIABLE_LENGTH_CMD ; 
 int VENDOR_SPECIFIC_CDB ; 
 scalar_t__ WARN_ON (int) ; 
 size_t scnprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  scsi_opcode_sa_name (int,int,char const**,char const**) ; 
 int scsi_varlen_cdb_length (unsigned char const*) ; 

__attribute__((used)) static size_t scsi_format_opcode_name(char *buffer, size_t buf_len,
				      const unsigned char *cdbp)
{
	int sa, cdb0;
	const char *cdb_name = NULL, *sa_name = NULL;
	size_t off;

	cdb0 = cdbp[0];
	if (cdb0 == VARIABLE_LENGTH_CMD) {
		int len = scsi_varlen_cdb_length(cdbp);

		if (len < 10) {
			off = scnprintf(buffer, buf_len,
					"short variable length command, len=%d",
					len);
			return off;
		}
		sa = (cdbp[8] << 8) + cdbp[9];
	} else
		sa = cdbp[1] & 0x1f;

	if (!scsi_opcode_sa_name(cdb0, sa, &cdb_name, &sa_name)) {
		if (cdb_name)
			off = scnprintf(buffer, buf_len, "%s", cdb_name);
		else {
			off = scnprintf(buffer, buf_len, "opcode=0x%x", cdb0);
			if (WARN_ON(off >= buf_len))
				return off;
			if (cdb0 >= VENDOR_SPECIFIC_CDB)
				off += scnprintf(buffer + off, buf_len - off,
						 " (vendor)");
			else if (cdb0 >= 0x60 && cdb0 < 0x7e)
				off += scnprintf(buffer + off, buf_len - off,
						 " (reserved)");
		}
	} else {
		if (sa_name)
			off = scnprintf(buffer, buf_len, "%s", sa_name);
		else if (cdb_name)
			off = scnprintf(buffer, buf_len, "%s, sa=0x%x",
					cdb_name, sa);
		else
			off = scnprintf(buffer, buf_len,
					"opcode=0x%x, sa=0x%x", cdb0, sa);
	}
	WARN_ON(off >= buf_len);
	return off;
}