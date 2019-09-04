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
 size_t scnprintf (char*,size_t,char*,...) ; 
 char* scsi_extd_sense_format (unsigned char,unsigned char,char const**) ; 

__attribute__((used)) static size_t
scsi_format_extd_sense(char *buffer, size_t buf_len,
		       unsigned char asc, unsigned char ascq)
{
	size_t off = 0;
	const char *extd_sense_fmt = NULL;
	const char *extd_sense_str = scsi_extd_sense_format(asc, ascq,
							    &extd_sense_fmt);

	if (extd_sense_str) {
		off = scnprintf(buffer, buf_len, "Add. Sense: %s",
				extd_sense_str);
		if (extd_sense_fmt)
			off += scnprintf(buffer + off, buf_len - off,
					 "(%s%x)", extd_sense_fmt, ascq);
	} else {
		if (asc >= 0x80)
			off = scnprintf(buffer, buf_len, "<<vendor>>");
		off += scnprintf(buffer + off, buf_len - off,
				 "ASC=0x%x ", asc);
		if (ascq >= 0x80)
			off += scnprintf(buffer + off, buf_len - off,
					 "<<vendor>>");
		off += scnprintf(buffer + off, buf_len - off,
				 "ASCQ=0x%x ", ascq);
	}
	return off;
}