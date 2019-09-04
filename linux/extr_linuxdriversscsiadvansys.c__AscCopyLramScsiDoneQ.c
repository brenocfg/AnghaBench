#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  void* uchar ;
typedef  int u32 ;
struct TYPE_3__ {int remain_bytes; void* extra_bytes; void* sense_len; void* cntl; void* q_no; void* q_status; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  int /*<<< orphan*/  ASC_SCSIQ_3 ;
typedef  int /*<<< orphan*/  ASC_SCSIQ_2 ;
typedef  TYPE_1__ ASC_QDONE_INFO ;

/* Variables and functions */
 scalar_t__ ASC_SCSIQ_B_CNTL ; 
 scalar_t__ ASC_SCSIQ_B_SENSE_LEN ; 
 scalar_t__ ASC_SCSIQ_B_STATUS ; 
 int ASC_SCSIQ_DONE_INFO_BEG ; 
 scalar_t__ ASC_SCSIQ_DW_REMAIN_XFER_CNT ; 
 scalar_t__ ASC_SCSIQ_W_ALT_DC1 ; 
 int AscReadLramWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DvcGetQinfo (int /*<<< orphan*/ ,int,void**,int) ; 

__attribute__((used)) static uchar
_AscCopyLramScsiDoneQ(PortAddr iop_base,
		      ushort q_addr,
		      ASC_QDONE_INFO *scsiq, unsigned int max_dma_count)
{
	ushort _val;
	uchar sg_queue_cnt;

	DvcGetQinfo(iop_base,
		    q_addr + ASC_SCSIQ_DONE_INFO_BEG,
		    (uchar *)scsiq,
		    (sizeof(ASC_SCSIQ_2) + sizeof(ASC_SCSIQ_3)) / 2);

	_val = AscReadLramWord(iop_base,
			       (ushort)(q_addr + (ushort)ASC_SCSIQ_B_STATUS));
	scsiq->q_status = (uchar)_val;
	scsiq->q_no = (uchar)(_val >> 8);
	_val = AscReadLramWord(iop_base,
			       (ushort)(q_addr + (ushort)ASC_SCSIQ_B_CNTL));
	scsiq->cntl = (uchar)_val;
	sg_queue_cnt = (uchar)(_val >> 8);
	_val = AscReadLramWord(iop_base,
			       (ushort)(q_addr +
					(ushort)ASC_SCSIQ_B_SENSE_LEN));
	scsiq->sense_len = (uchar)_val;
	scsiq->extra_bytes = (uchar)(_val >> 8);

	/*
	 * Read high word of remain bytes from alternate location.
	 */
	scsiq->remain_bytes = (((u32)AscReadLramWord(iop_base,
						     (ushort)(q_addr +
							      (ushort)
							      ASC_SCSIQ_W_ALT_DC1)))
			       << 16);
	/*
	 * Read low word of remain bytes from original location.
	 */
	scsiq->remain_bytes += AscReadLramWord(iop_base,
					       (ushort)(q_addr + (ushort)
							ASC_SCSIQ_DW_REMAIN_XFER_CNT));

	scsiq->remain_bytes &= max_dma_count;
	return sg_queue_cnt;
}