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
struct rds_header {unsigned char* h_exthdr; } ;

/* Variables and functions */
 unsigned char RDS_EXTHDR_NONE ; 
 unsigned int RDS_HEADER_EXT_SPACE ; 
 unsigned int __RDS_EXTHDR_MAX ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,unsigned int) ; 
 unsigned int* rds_exthdr_size ; 

int rds_message_add_extension(struct rds_header *hdr, unsigned int type,
			      const void *data, unsigned int len)
{
	unsigned int ext_len = sizeof(u8) + len;
	unsigned char *dst;

	/* For now, refuse to add more than one extension header */
	if (hdr->h_exthdr[0] != RDS_EXTHDR_NONE)
		return 0;

	if (type >= __RDS_EXTHDR_MAX || len != rds_exthdr_size[type])
		return 0;

	if (ext_len >= RDS_HEADER_EXT_SPACE)
		return 0;
	dst = hdr->h_exthdr;

	*dst++ = type;
	memcpy(dst, data, len);

	dst[len] = RDS_EXTHDR_NONE;
	return 1;
}