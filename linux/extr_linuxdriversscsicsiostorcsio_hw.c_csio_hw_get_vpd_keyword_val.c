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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct t4_vpd_hdr {scalar_t__ id_tag; scalar_t__ vpdr_tag; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VPD_INFO_FLD_HDR_SIZE ; 
 scalar_t__ VPD_LEN ; 
 scalar_t__ memcmp (scalar_t__ const*,char const*,int) ; 

__attribute__((used)) static int
csio_hw_get_vpd_keyword_val(const struct t4_vpd_hdr *v, const char *kw)
{
	int32_t i;
	int32_t offset , len;
	const uint8_t *buf = &v->id_tag;
	const uint8_t *vpdr_len = &v->vpdr_tag;
	offset = sizeof(struct t4_vpd_hdr);
	len =  (uint16_t)vpdr_len[1] + ((uint16_t)vpdr_len[2] << 8);

	if (len + sizeof(struct t4_vpd_hdr) > VPD_LEN)
		return -EINVAL;

	for (i = offset; (i + VPD_INFO_FLD_HDR_SIZE) <= (offset + len);) {
		if (memcmp(buf + i , kw, 2) == 0) {
			i += VPD_INFO_FLD_HDR_SIZE;
			return i;
		}

		i += VPD_INFO_FLD_HDR_SIZE + buf[i+2];
	}

	return -EINVAL;
}