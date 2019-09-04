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
struct scsi_tape {scalar_t__ ready; unsigned char c_algo; int compression_changed; TYPE_1__* buffer; } ;
struct TYPE_2__ {unsigned char* b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSION_PAGE ; 
 int CP_OFF_C_ALGO ; 
 int CP_OFF_DCE_DCC ; 
 unsigned char DCC_MASK ; 
 unsigned char DCE_MASK ; 
 int /*<<< orphan*/  DEBC_printk (struct scsi_tape*,char*,...) ; 
 int EIO ; 
 size_t MH_OFF_BDESCS_LENGTH ; 
 unsigned char MODE_HEADER_LENGTH ; 
 scalar_t__ ST_READY ; 
 int read_mode_page (struct scsi_tape*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_mode_page (struct scsi_tape*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_compression(struct scsi_tape * STp, int state)
{
	int retval;
	int mpoffs;  /* Offset to mode page start */
	unsigned char *b_data = (STp->buffer)->b_data;

	if (STp->ready != ST_READY)
		return (-EIO);

	/* Read the current page contents */
	retval = read_mode_page(STp, COMPRESSION_PAGE, 0);
	if (retval) {
		DEBC_printk(STp, "Compression mode page not supported.\n");
		return (-EIO);
	}

	mpoffs = MODE_HEADER_LENGTH + b_data[MH_OFF_BDESCS_LENGTH];
	DEBC_printk(STp, "Compression state is %d.\n",
		    (b_data[mpoffs + CP_OFF_DCE_DCC] & DCE_MASK ? 1 : 0));

	/* Check if compression can be changed */
	if ((b_data[mpoffs + CP_OFF_DCE_DCC] & DCC_MASK) == 0) {
		DEBC_printk(STp, "Compression not supported.\n");
		return (-EIO);
	}

	/* Do the change */
	if (state) {
		b_data[mpoffs + CP_OFF_DCE_DCC] |= DCE_MASK;
		if (STp->c_algo != 0)
			b_data[mpoffs + CP_OFF_C_ALGO] = STp->c_algo;
	}
	else {
		b_data[mpoffs + CP_OFF_DCE_DCC] &= ~DCE_MASK;
		if (STp->c_algo != 0)
			b_data[mpoffs + CP_OFF_C_ALGO] = 0; /* no compression */
	}

	retval = write_mode_page(STp, COMPRESSION_PAGE, 0);
	if (retval) {
		DEBC_printk(STp, "Compression change failed.\n");
		return (-EIO);
	}
	DEBC_printk(STp, "Compression state changed to %d.\n", state);

	STp->compression_changed = 1;
	return 0;
}