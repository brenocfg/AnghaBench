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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int TOLOWER (char) ; 
 unsigned int US_FL_ALWAYS_SYNC ; 
 unsigned int US_FL_BAD_SENSE ; 
 unsigned int US_FL_CAPACITY_HEURISTICS ; 
 unsigned int US_FL_CAPACITY_OK ; 
 unsigned int US_FL_FIX_CAPACITY ; 
 unsigned int US_FL_IGNORE_DEVICE ; 
 unsigned int US_FL_IGNORE_RESIDUE ; 
 unsigned int US_FL_IGNORE_UAS ; 
 unsigned int US_FL_INITIAL_READ10 ; 
 unsigned int US_FL_MAX_SECTORS_240 ; 
 unsigned int US_FL_MAX_SECTORS_64 ; 
 unsigned int US_FL_NOT_LOCKABLE ; 
 unsigned int US_FL_NO_ATA_1X ; 
 unsigned int US_FL_NO_READ_CAPACITY_16 ; 
 unsigned int US_FL_NO_READ_DISC_INFO ; 
 unsigned int US_FL_NO_REPORT_LUNS ; 
 unsigned int US_FL_NO_REPORT_OPCODES ; 
 unsigned int US_FL_NO_WP_DETECT ; 
 unsigned int US_FL_SANE_SENSE ; 
 unsigned int US_FL_SINGLE_LUN ; 
 unsigned int US_FL_WRITE_CACHE ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 char* quirks ; 
 scalar_t__ simple_strtoul (char*,char**,int) ; 

void usb_stor_adjust_quirks(struct usb_device *udev, unsigned long *fflags)
{
	char *p;
	u16 vid = le16_to_cpu(udev->descriptor.idVendor);
	u16 pid = le16_to_cpu(udev->descriptor.idProduct);
	unsigned f = 0;
	unsigned int mask = (US_FL_SANE_SENSE | US_FL_BAD_SENSE |
			US_FL_FIX_CAPACITY | US_FL_IGNORE_UAS |
			US_FL_CAPACITY_HEURISTICS | US_FL_IGNORE_DEVICE |
			US_FL_NOT_LOCKABLE | US_FL_MAX_SECTORS_64 |
			US_FL_CAPACITY_OK | US_FL_IGNORE_RESIDUE |
			US_FL_SINGLE_LUN | US_FL_NO_WP_DETECT |
			US_FL_NO_READ_DISC_INFO | US_FL_NO_READ_CAPACITY_16 |
			US_FL_INITIAL_READ10 | US_FL_WRITE_CACHE |
			US_FL_NO_ATA_1X | US_FL_NO_REPORT_OPCODES |
			US_FL_MAX_SECTORS_240 | US_FL_NO_REPORT_LUNS |
			US_FL_ALWAYS_SYNC);

	p = quirks;
	while (*p) {
		/* Each entry consists of VID:PID:flags */
		if (vid == simple_strtoul(p, &p, 16) &&
				*p == ':' &&
				pid == simple_strtoul(p+1, &p, 16) &&
				*p == ':')
			break;

		/* Move forward to the next entry */
		while (*p) {
			if (*p++ == ',')
				break;
		}
	}
	if (!*p)	/* No match */
		return;

	/* Collect the flags */
	while (*++p && *p != ',') {
		switch (TOLOWER(*p)) {
		case 'a':
			f |= US_FL_SANE_SENSE;
			break;
		case 'b':
			f |= US_FL_BAD_SENSE;
			break;
		case 'c':
			f |= US_FL_FIX_CAPACITY;
			break;
		case 'd':
			f |= US_FL_NO_READ_DISC_INFO;
			break;
		case 'e':
			f |= US_FL_NO_READ_CAPACITY_16;
			break;
		case 'f':
			f |= US_FL_NO_REPORT_OPCODES;
			break;
		case 'g':
			f |= US_FL_MAX_SECTORS_240;
			break;
		case 'h':
			f |= US_FL_CAPACITY_HEURISTICS;
			break;
		case 'i':
			f |= US_FL_IGNORE_DEVICE;
			break;
		case 'j':
			f |= US_FL_NO_REPORT_LUNS;
			break;
		case 'l':
			f |= US_FL_NOT_LOCKABLE;
			break;
		case 'm':
			f |= US_FL_MAX_SECTORS_64;
			break;
		case 'n':
			f |= US_FL_INITIAL_READ10;
			break;
		case 'o':
			f |= US_FL_CAPACITY_OK;
			break;
		case 'p':
			f |= US_FL_WRITE_CACHE;
			break;
		case 'r':
			f |= US_FL_IGNORE_RESIDUE;
			break;
		case 's':
			f |= US_FL_SINGLE_LUN;
			break;
		case 't':
			f |= US_FL_NO_ATA_1X;
			break;
		case 'u':
			f |= US_FL_IGNORE_UAS;
			break;
		case 'w':
			f |= US_FL_NO_WP_DETECT;
			break;
		case 'y':
			f |= US_FL_ALWAYS_SYNC;
			break;
		/* Ignore unrecognized flag characters */
		}
	}
	*fflags = (*fflags & ~mask) | f;
}