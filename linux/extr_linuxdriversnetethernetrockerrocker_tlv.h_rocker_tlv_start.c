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
struct rocker_desc_info {int tlv_size; scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct rocker_tlv *
rocker_tlv_start(struct rocker_desc_info *desc_info)
{
	return (struct rocker_tlv *) ((char *) desc_info->data +
					       desc_info->tlv_size);
}