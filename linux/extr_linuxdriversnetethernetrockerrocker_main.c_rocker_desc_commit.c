#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rocker_desc_info {int /*<<< orphan*/  tlv_size; TYPE_1__* desc; int /*<<< orphan*/  data_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  tlv_size; int /*<<< orphan*/  buf_size; } ;

/* Variables and functions */

__attribute__((used)) static void rocker_desc_commit(const struct rocker_desc_info *desc_info)
{
	desc_info->desc->buf_size = desc_info->data_size;
	desc_info->desc->tlv_size = desc_info->tlv_size;
}