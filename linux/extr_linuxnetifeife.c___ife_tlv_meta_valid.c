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
typedef  scalar_t__ u16 ;
struct meta_tlvhdr {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int NLA_ALIGN (scalar_t__) ; 
 scalar_t__ NLA_HDRLEN ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool __ife_tlv_meta_valid(const unsigned char *skbdata,
				 const unsigned char *ifehdr_end)
{
	const struct meta_tlvhdr *tlv;
	u16 tlvlen;

	if (unlikely(skbdata + sizeof(*tlv) > ifehdr_end))
		return false;

	tlv = (const struct meta_tlvhdr *)skbdata;
	tlvlen = ntohs(tlv->len);

	/* tlv length field is inc header, check on minimum */
	if (tlvlen < NLA_HDRLEN)
		return false;

	/* overflow by NLA_ALIGN check */
	if (NLA_ALIGN(tlvlen) < tlvlen)
		return false;

	if (unlikely(skbdata + NLA_ALIGN(tlvlen) > ifehdr_end))
		return false;

	return true;
}