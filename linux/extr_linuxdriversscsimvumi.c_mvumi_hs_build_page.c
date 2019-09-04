#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mvumi_hs_page4 {void* ib_depth; void* ob_depth; int /*<<< orphan*/  ob_entry_size; int /*<<< orphan*/  ib_entry_size; void* ob_baseaddr_h; void* ob_baseaddr_l; void* ib_baseaddr_h; void* ib_baseaddr_l; } ;
struct mvumi_hs_page3 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ver_build; int /*<<< orphan*/  ver_oem; int /*<<< orphan*/  ver_minor; int /*<<< orphan*/  ver_major; } ;
struct mvumi_hs_page2 {int host_type; int host_cap; int /*<<< orphan*/  seconds_since1970; int /*<<< orphan*/  intr_vector; int /*<<< orphan*/  intr_level; int /*<<< orphan*/  slot_number; int /*<<< orphan*/  system_io_bus; TYPE_1__ host_ver; } ;
struct mvumi_hs_header {int page_code; int frame_length; void* checksum; int /*<<< orphan*/  frame_content; } ;
struct mvumi_hba {int hba_capability; TYPE_2__* pdev; int /*<<< orphan*/  list_num_io; int /*<<< orphan*/  ob_max_size_setting; int /*<<< orphan*/  ib_max_size_setting; int /*<<< orphan*/  ob_list_phys; int /*<<< orphan*/  ib_list_phys; } ;
struct TYPE_6__ {int tz_minuteswest; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int HS_CAPABILITY_NEW_PAGE_IO_DEPTH_DEF ; 
 int HS_CAPABILITY_SUPPORT_DYN_SRC ; 
#define  HS_PAGE_CL_INFO 130 
#define  HS_PAGE_FIRM_CTL 129 
#define  HS_PAGE_HOST_INFO 128 
 int /*<<< orphan*/  VER_BUILD ; 
 int /*<<< orphan*/  VER_MAJOR ; 
 int /*<<< orphan*/  VER_MINOR ; 
 int /*<<< orphan*/  VER_OEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* find_first_bit (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* mvumi_calculate_checksum (struct mvumi_hs_header*,int) ; 
 TYPE_3__ sys_tz ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvumi_hs_build_page(struct mvumi_hba *mhba,
				struct mvumi_hs_header *hs_header)
{
	struct mvumi_hs_page2 *hs_page2;
	struct mvumi_hs_page4 *hs_page4;
	struct mvumi_hs_page3 *hs_page3;
	u64 time;
	u64 local_time;

	switch (hs_header->page_code) {
	case HS_PAGE_HOST_INFO:
		hs_page2 = (struct mvumi_hs_page2 *) hs_header;
		hs_header->frame_length = sizeof(*hs_page2) - 4;
		memset(hs_header->frame_content, 0, hs_header->frame_length);
		hs_page2->host_type = 3; /* 3 mean linux*/
		if (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC)
			hs_page2->host_cap = 0x08;/* host dynamic source mode */
		hs_page2->host_ver.ver_major = VER_MAJOR;
		hs_page2->host_ver.ver_minor = VER_MINOR;
		hs_page2->host_ver.ver_oem = VER_OEM;
		hs_page2->host_ver.ver_build = VER_BUILD;
		hs_page2->system_io_bus = 0;
		hs_page2->slot_number = 0;
		hs_page2->intr_level = 0;
		hs_page2->intr_vector = 0;
		time = ktime_get_real_seconds();
		local_time = (time - (sys_tz.tz_minuteswest * 60));
		hs_page2->seconds_since1970 = local_time;
		hs_header->checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
		break;

	case HS_PAGE_FIRM_CTL:
		hs_page3 = (struct mvumi_hs_page3 *) hs_header;
		hs_header->frame_length = sizeof(*hs_page3) - 4;
		memset(hs_header->frame_content, 0, hs_header->frame_length);
		hs_header->checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
		break;

	case HS_PAGE_CL_INFO:
		hs_page4 = (struct mvumi_hs_page4 *) hs_header;
		hs_header->frame_length = sizeof(*hs_page4) - 4;
		memset(hs_header->frame_content, 0, hs_header->frame_length);
		hs_page4->ib_baseaddr_l = lower_32_bits(mhba->ib_list_phys);
		hs_page4->ib_baseaddr_h = upper_32_bits(mhba->ib_list_phys);

		hs_page4->ob_baseaddr_l = lower_32_bits(mhba->ob_list_phys);
		hs_page4->ob_baseaddr_h = upper_32_bits(mhba->ob_list_phys);
		hs_page4->ib_entry_size = mhba->ib_max_size_setting;
		hs_page4->ob_entry_size = mhba->ob_max_size_setting;
		if (mhba->hba_capability
			& HS_CAPABILITY_NEW_PAGE_IO_DEPTH_DEF) {
			hs_page4->ob_depth = find_first_bit((unsigned long *)
							    &mhba->list_num_io,
							    BITS_PER_LONG);
			hs_page4->ib_depth = find_first_bit((unsigned long *)
							    &mhba->list_num_io,
							    BITS_PER_LONG);
		} else {
			hs_page4->ob_depth = (u8) mhba->list_num_io;
			hs_page4->ib_depth = (u8) mhba->list_num_io;
		}
		hs_header->checksum = mvumi_calculate_checksum(hs_header,
						hs_header->frame_length);
		break;

	default:
		dev_err(&mhba->pdev->dev, "cannot build page, code[0x%x]\n",
			hs_header->page_code);
		break;
	}
}