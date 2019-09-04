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
typedef  int /*<<< orphan*/  u32 ;
struct sas_identify_frame {int _un1; int phy_id; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/ * _un4_11; int /*<<< orphan*/  target_bits; int /*<<< orphan*/  initiator_bits; scalar_t__ frame_type; int /*<<< orphan*/  dev_type; } ;
struct hisi_hba {int /*<<< orphan*/  sas_addr; } ;
typedef  int /*<<< orphan*/  identify_frame ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 int /*<<< orphan*/  SAS_PROTOCOL_NONE ; 
 int /*<<< orphan*/  TX_ID_DWORD0 ; 
 int /*<<< orphan*/  TX_ID_DWORD1 ; 
 int /*<<< orphan*/  TX_ID_DWORD2 ; 
 int /*<<< orphan*/  TX_ID_DWORD3 ; 
 int /*<<< orphan*/  TX_ID_DWORD4 ; 
 int /*<<< orphan*/  TX_ID_DWORD5 ; 
 int /*<<< orphan*/  __swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_phy_write32 (struct hisi_hba*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sas_identify_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void config_id_frame_v1_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	struct sas_identify_frame identify_frame;
	u32 *identify_buffer;

	memset(&identify_frame, 0, sizeof(identify_frame));
	identify_frame.dev_type = SAS_END_DEVICE;
	identify_frame.frame_type = 0;
	identify_frame._un1 = 1;
	identify_frame.initiator_bits = SAS_PROTOCOL_ALL;
	identify_frame.target_bits = SAS_PROTOCOL_NONE;
	memcpy(&identify_frame._un4_11[0], hisi_hba->sas_addr, SAS_ADDR_SIZE);
	memcpy(&identify_frame.sas_addr[0], hisi_hba->sas_addr,	SAS_ADDR_SIZE);
	identify_frame.phy_id = phy_no;
	identify_buffer = (u32 *)(&identify_frame);

	hisi_sas_phy_write32(hisi_hba, phy_no, TX_ID_DWORD0,
			__swab32(identify_buffer[0]));
	hisi_sas_phy_write32(hisi_hba, phy_no, TX_ID_DWORD1,
			__swab32(identify_buffer[1]));
	hisi_sas_phy_write32(hisi_hba, phy_no, TX_ID_DWORD2,
			__swab32(identify_buffer[2]));
	hisi_sas_phy_write32(hisi_hba, phy_no, TX_ID_DWORD3,
			__swab32(identify_buffer[3]));
	hisi_sas_phy_write32(hisi_hba, phy_no, TX_ID_DWORD4,
			__swab32(identify_buffer[4]));
	hisi_sas_phy_write32(hisi_hba, phy_no, TX_ID_DWORD5,
			__swab32(identify_buffer[5]));
}