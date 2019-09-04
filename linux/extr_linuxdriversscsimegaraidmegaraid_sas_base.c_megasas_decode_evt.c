#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ class; int /*<<< orphan*/  locale; } ;
union megasas_evt_class_locale {TYPE_2__ members; int /*<<< orphan*/  word; } ;
struct megasas_instance {TYPE_3__* pdev; struct megasas_evt_detail* evt_detail; } ;
struct TYPE_4__ {int /*<<< orphan*/  word; } ;
struct megasas_evt_detail {int /*<<< orphan*/  description; int /*<<< orphan*/  time_stamp; int /*<<< orphan*/  seq_num; TYPE_1__ cl; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MFI_EVT_CLASS_CRITICAL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_class (scalar_t__) ; 
 int /*<<< orphan*/  format_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
megasas_decode_evt(struct megasas_instance *instance)
{
	struct megasas_evt_detail *evt_detail = instance->evt_detail;
	union megasas_evt_class_locale class_locale;
	class_locale.word = le32_to_cpu(evt_detail->cl.word);

	if (class_locale.members.class >= MFI_EVT_CLASS_CRITICAL)
		dev_info(&instance->pdev->dev, "%d (%s/0x%04x/%s) - %s\n",
			le32_to_cpu(evt_detail->seq_num),
			format_timestamp(le32_to_cpu(evt_detail->time_stamp)),
			(class_locale.members.locale),
			format_class(class_locale.members.class),
			evt_detail->description);
}