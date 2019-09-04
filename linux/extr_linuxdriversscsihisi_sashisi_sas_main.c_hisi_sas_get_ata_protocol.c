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
typedef  int /*<<< orphan*/  u8 ;
struct host_to_dev_fis {int command; int /*<<< orphan*/  features; } ;

/* Variables and functions */
#define  ATA_CMD_CHK_POWER 175 
#define  ATA_CMD_DEV_RESET 174 
#define  ATA_CMD_DOWNLOAD_MICRO 173 
#define  ATA_CMD_DOWNLOAD_MICRO_DMA 172 
#define  ATA_CMD_DSM 171 
#define  ATA_CMD_EDD 170 
#define  ATA_CMD_FLUSH 169 
#define  ATA_CMD_FLUSH_EXT 168 
#define  ATA_CMD_FPDMA_READ 167 
#define  ATA_CMD_FPDMA_RECV 166 
#define  ATA_CMD_FPDMA_SEND 165 
#define  ATA_CMD_FPDMA_WRITE 164 
#define  ATA_CMD_ID_ATA 163 
#define  ATA_CMD_NCQ_NON_DATA 162 
#define  ATA_CMD_PIO_READ 161 
#define  ATA_CMD_PIO_READ_EXT 160 
#define  ATA_CMD_PIO_WRITE 159 
#define  ATA_CMD_PIO_WRITE_EXT 158 
#define  ATA_CMD_PMP_READ 157 
#define  ATA_CMD_PMP_READ_DMA 156 
#define  ATA_CMD_PMP_WRITE 155 
#define  ATA_CMD_PMP_WRITE_DMA 154 
#define  ATA_CMD_READ 153 
#define  ATA_CMD_READ_EXT 152 
#define  ATA_CMD_READ_LOG_DMA_EXT 151 
#define  ATA_CMD_READ_LOG_EXT 150 
#define  ATA_CMD_READ_STREAM_DMA_EXT 149 
#define  ATA_CMD_SET_FEATURES 148 
#define  ATA_CMD_SET_MAX 147 
#define  ATA_CMD_STANDBY 146 
#define  ATA_CMD_STANDBYNOW1 145 
#define  ATA_CMD_TRUSTED_RCV_DMA 144 
#define  ATA_CMD_TRUSTED_SND_DMA 143 
#define  ATA_CMD_VERIFY 142 
#define  ATA_CMD_VERIFY_EXT 141 
#define  ATA_CMD_WRITE 140 
#define  ATA_CMD_WRITE_EXT 139 
#define  ATA_CMD_WRITE_FUA_EXT 138 
#define  ATA_CMD_WRITE_LOG_DMA_EXT 137 
#define  ATA_CMD_WRITE_LOG_EXT 136 
#define  ATA_CMD_WRITE_QUEUED 135 
#define  ATA_CMD_WRITE_STREAM_DMA_EXT 134 
#define  ATA_CMD_ZAC_MGMT_IN 133 
#define  ATA_CMD_ZAC_MGMT_OUT 132 
#define  ATA_SET_MAX_LOCK 131 
#define  ATA_SET_MAX_PASSWD 130 
#define  ATA_SET_MAX_PASSWD_DMA 129 
#define  ATA_SET_MAX_UNLOCK_DMA 128 
 int DMA_NONE ; 
 int /*<<< orphan*/  HISI_SAS_SATA_PROTOCOL_DMA ; 
 int /*<<< orphan*/  HISI_SAS_SATA_PROTOCOL_FPDMA ; 
 int /*<<< orphan*/  HISI_SAS_SATA_PROTOCOL_NONDATA ; 
 int /*<<< orphan*/  HISI_SAS_SATA_PROTOCOL_PIO ; 

u8 hisi_sas_get_ata_protocol(struct host_to_dev_fis *fis, int direction)
{
	switch (fis->command) {
	case ATA_CMD_FPDMA_WRITE:
	case ATA_CMD_FPDMA_READ:
	case ATA_CMD_FPDMA_RECV:
	case ATA_CMD_FPDMA_SEND:
	case ATA_CMD_NCQ_NON_DATA:
		return HISI_SAS_SATA_PROTOCOL_FPDMA;

	case ATA_CMD_DOWNLOAD_MICRO:
	case ATA_CMD_ID_ATA:
	case ATA_CMD_PMP_READ:
	case ATA_CMD_READ_LOG_EXT:
	case ATA_CMD_PIO_READ:
	case ATA_CMD_PIO_READ_EXT:
	case ATA_CMD_PMP_WRITE:
	case ATA_CMD_WRITE_LOG_EXT:
	case ATA_CMD_PIO_WRITE:
	case ATA_CMD_PIO_WRITE_EXT:
		return HISI_SAS_SATA_PROTOCOL_PIO;

	case ATA_CMD_DSM:
	case ATA_CMD_DOWNLOAD_MICRO_DMA:
	case ATA_CMD_PMP_READ_DMA:
	case ATA_CMD_PMP_WRITE_DMA:
	case ATA_CMD_READ:
	case ATA_CMD_READ_EXT:
	case ATA_CMD_READ_LOG_DMA_EXT:
	case ATA_CMD_READ_STREAM_DMA_EXT:
	case ATA_CMD_TRUSTED_RCV_DMA:
	case ATA_CMD_TRUSTED_SND_DMA:
	case ATA_CMD_WRITE:
	case ATA_CMD_WRITE_EXT:
	case ATA_CMD_WRITE_FUA_EXT:
	case ATA_CMD_WRITE_QUEUED:
	case ATA_CMD_WRITE_LOG_DMA_EXT:
	case ATA_CMD_WRITE_STREAM_DMA_EXT:
	case ATA_CMD_ZAC_MGMT_IN:
		return HISI_SAS_SATA_PROTOCOL_DMA;

	case ATA_CMD_CHK_POWER:
	case ATA_CMD_DEV_RESET:
	case ATA_CMD_EDD:
	case ATA_CMD_FLUSH:
	case ATA_CMD_FLUSH_EXT:
	case ATA_CMD_VERIFY:
	case ATA_CMD_VERIFY_EXT:
	case ATA_CMD_SET_FEATURES:
	case ATA_CMD_STANDBY:
	case ATA_CMD_STANDBYNOW1:
	case ATA_CMD_ZAC_MGMT_OUT:
		return HISI_SAS_SATA_PROTOCOL_NONDATA;

	case ATA_CMD_SET_MAX:
		switch (fis->features) {
		case ATA_SET_MAX_PASSWD:
		case ATA_SET_MAX_LOCK:
			return HISI_SAS_SATA_PROTOCOL_PIO;

		case ATA_SET_MAX_PASSWD_DMA:
		case ATA_SET_MAX_UNLOCK_DMA:
			return HISI_SAS_SATA_PROTOCOL_DMA;

		default:
			return HISI_SAS_SATA_PROTOCOL_NONDATA;
		}

	default:
	{
		if (direction == DMA_NONE)
			return HISI_SAS_SATA_PROTOCOL_NONDATA;
		return HISI_SAS_SATA_PROTOCOL_PIO;
	}
	}
}