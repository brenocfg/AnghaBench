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
struct TYPE_3__ {int aud_en; } ;
struct TYPE_4__ {int /*<<< orphan*/  regval; TYPE_1__ regx; } ;
struct snd_intelhad {TYPE_2__ aud_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_CONFIG ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void had_enable_audio(struct snd_intelhad *intelhaddata,
			     bool enable)
{
	/* update the cached value */
	intelhaddata->aud_config.regx.aud_en = enable;
	had_write_register(intelhaddata, AUD_CONFIG,
			   intelhaddata->aud_config.regval);
}