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
struct tlv_desc {int dummy; } ;

/* Variables and functions */
 int TLV_GET_LEN (struct tlv_desc*) ; 
 int TLV_SPACE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int TLV_GET_DATA_LEN(struct tlv_desc *tlv)
{
	return TLV_GET_LEN(tlv) - TLV_SPACE(0);
}