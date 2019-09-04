#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_info; TYPE_1__ layer; } ;
struct cfctrl {TYPE_2__ serv; } ;
struct caif_payload_info {int /*<<< orphan*/ * dev_info; int /*<<< orphan*/  channel_id; scalar_t__ hdr_len; } ;

/* Variables and functions */

__attribute__((used)) static void init_info(struct caif_payload_info *info, struct cfctrl *cfctrl)
{
	info->hdr_len = 0;
	info->channel_id = cfctrl->serv.layer.id;
	info->dev_info = &cfctrl->serv.dev_info;
}