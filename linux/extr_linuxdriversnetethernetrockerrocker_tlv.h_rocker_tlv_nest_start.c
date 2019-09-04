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
struct rocker_tlv {int dummy; } ;
struct rocker_desc_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ rocker_tlv_put (struct rocker_desc_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rocker_tlv* rocker_tlv_start (struct rocker_desc_info*) ; 

__attribute__((used)) static inline struct rocker_tlv *
rocker_tlv_nest_start(struct rocker_desc_info *desc_info, int attrtype)
{
	struct rocker_tlv *start = rocker_tlv_start(desc_info);

	if (rocker_tlv_put(desc_info, attrtype, 0, NULL) < 0)
		return NULL;

	return start;
}