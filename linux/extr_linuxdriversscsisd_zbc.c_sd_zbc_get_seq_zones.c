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
typedef  unsigned char u8 ;
typedef  int u32 ;
struct scsi_disk {int capacity; } ;
typedef  int sector_t ;

/* Variables and functions */
 unsigned char ZBC_ZONE_COND_OFFLINE ; 
 unsigned char ZBC_ZONE_COND_READONLY ; 
 unsigned char ZBC_ZONE_TYPE_CONV ; 
 int get_unaligned_be32 (unsigned char*) ; 
 int get_unaligned_be64 (unsigned char*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static sector_t sd_zbc_get_seq_zones(struct scsi_disk *sdkp, unsigned char *buf,
				     unsigned int buflen, u32 zone_shift,
				     unsigned long *seq_zones_bitmap)
{
	sector_t lba, next_lba = sdkp->capacity;
	unsigned int buf_len, list_length;
	unsigned char *rec;
	u8 type, cond;

	list_length = get_unaligned_be32(&buf[0]) + 64;
	buf_len = min(list_length, buflen);
	rec = buf + 64;

	while (rec < buf + buf_len) {
		type = rec[0] & 0x0f;
		cond = (rec[1] >> 4) & 0xf;
		lba = get_unaligned_be64(&rec[16]);
		if (type != ZBC_ZONE_TYPE_CONV &&
		    cond != ZBC_ZONE_COND_READONLY &&
		    cond != ZBC_ZONE_COND_OFFLINE)
			set_bit(lba >> zone_shift, seq_zones_bitmap);
		next_lba = lba + get_unaligned_be64(&rec[8]);
		rec += 64;
	}

	return next_lba;
}