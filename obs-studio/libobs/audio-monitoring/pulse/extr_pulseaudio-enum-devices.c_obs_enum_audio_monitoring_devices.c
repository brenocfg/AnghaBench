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
struct enum_cb {int cont; void* data; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  pa_source_info_cb_t ;
typedef  int /*<<< orphan*/  obs_enum_audio_device_cb ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct enum_cb*) ; 
 struct enum_cb* bzalloc (int) ; 
 int /*<<< orphan*/  pulseaudio_get_source_info_list (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pulseaudio_init () ; 
 int /*<<< orphan*/  pulseaudio_output_info ; 
 int /*<<< orphan*/  pulseaudio_unref () ; 

void obs_enum_audio_monitoring_devices(obs_enum_audio_device_cb cb, void *data)
{
	struct enum_cb *ecb = bzalloc(sizeof(struct enum_cb));
	ecb->cb = cb;
	ecb->data = data;
	ecb->cont = 1;

	pulseaudio_init();
	pa_source_info_cb_t pa_cb = pulseaudio_output_info;
	pulseaudio_get_source_info_list(pa_cb, (void *)ecb);
	pulseaudio_unref();

	bfree(ecb);
}