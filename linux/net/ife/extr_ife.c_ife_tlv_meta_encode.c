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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NLA_HDRLEN ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int nla_total_size (int) ; 

int ife_tlv_meta_encode(void *skbdata, u16 attrtype, u16 dlen, const void *dval)
{
	__be32 *tlv = (__be32 *) (skbdata);
	u16 totlen = nla_total_size(dlen);	/*alignment + hdr */
	char *dptr = (char *) tlv + NLA_HDRLEN;
	u32 htlv = attrtype << 16 | (dlen + NLA_HDRLEN);

	*tlv = htonl(htlv);
	memset(dptr, 0, totlen - NLA_HDRLEN);
	memcpy(dptr, dval, dlen);

	return totlen;
}