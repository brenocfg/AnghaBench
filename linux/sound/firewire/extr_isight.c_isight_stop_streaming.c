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
struct isight {scalar_t__ audio_base; int /*<<< orphan*/  unit; int /*<<< orphan*/  resources; int /*<<< orphan*/ * context; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  FW_QUIET ; 
 scalar_t__ REG_AUDIO_ENABLE ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_context_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_iso_resources_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isight_stop_streaming(struct isight *isight)
{
	__be32 value;

	if (!isight->context)
		return;

	fw_iso_context_stop(isight->context);
	fw_iso_context_destroy(isight->context);
	isight->context = NULL;
	fw_iso_resources_free(&isight->resources);
	value = 0;
	snd_fw_transaction(isight->unit, TCODE_WRITE_QUADLET_REQUEST,
			   isight->audio_base + REG_AUDIO_ENABLE,
			   &value, 4, FW_QUIET);
}