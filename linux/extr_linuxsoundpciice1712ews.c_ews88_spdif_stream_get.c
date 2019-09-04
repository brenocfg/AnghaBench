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
struct TYPE_4__ {int /*<<< orphan*/  cs8403_stream_bits; } ;
struct snd_ice1712 {TYPE_2__ spdif; } ;
struct TYPE_3__ {int /*<<< orphan*/  iec958; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cs8404_decode_spdif_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ews88_spdif_stream_get(struct snd_ice1712 *ice, struct snd_ctl_elem_value *ucontrol)
{
	snd_cs8404_decode_spdif_bits(&ucontrol->value.iec958, ice->spdif.cs8403_stream_bits);
}