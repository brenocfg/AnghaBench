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
struct rocker_tlv {int type; int len; } ;
struct rocker_desc_info {int data_size; int tlv_size; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rocker_tlv_attr_size (int) ; 
 int /*<<< orphan*/  rocker_tlv_data (struct rocker_tlv*) ; 
 int /*<<< orphan*/  rocker_tlv_padlen (int) ; 
 struct rocker_tlv* rocker_tlv_start (struct rocker_desc_info*) ; 
 int rocker_tlv_total_size (int) ; 
 scalar_t__ unlikely (int) ; 

int rocker_tlv_put(struct rocker_desc_info *desc_info,
		   int attrtype, int attrlen, const void *data)
{
	int tail_room = desc_info->data_size - desc_info->tlv_size;
	int total_size = rocker_tlv_total_size(attrlen);
	struct rocker_tlv *tlv;

	if (unlikely(tail_room < total_size))
		return -EMSGSIZE;

	tlv = rocker_tlv_start(desc_info);
	desc_info->tlv_size += total_size;
	tlv->type = attrtype;
	tlv->len = rocker_tlv_attr_size(attrlen);
	memcpy(rocker_tlv_data(tlv), data, attrlen);
	memset((char *) tlv + tlv->len, 0, rocker_tlv_padlen(attrlen));
	return 0;
}