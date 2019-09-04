#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_24__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  void* uint32_t ;
struct resample_info {int /*<<< orphan*/  format; int /*<<< orphan*/  speakers; void* samples_per_sec; } ;
struct audio_output_info {int /*<<< orphan*/  speakers; void* samples_per_sec; } ;
struct audio_monitor {int ignore; TYPE_10__* client; int /*<<< orphan*/  playback_mutex; int /*<<< orphan*/  render; int /*<<< orphan*/  resampler; int /*<<< orphan*/  channels; void* sample_rate; TYPE_17__* device; TYPE_6__* source; } ;
struct TYPE_29__ {int output_flags; } ;
struct TYPE_35__ {TYPE_1__ info; } ;
typedef  TYPE_6__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;
struct TYPE_36__ {int /*<<< orphan*/  dwChannelMask; } ;
typedef  TYPE_7__ WAVEFORMATEXTENSIBLE ;
struct TYPE_37__ {int /*<<< orphan*/  nChannels; scalar_t__ nSamplesPerSec; } ;
typedef  TYPE_8__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_38__ {TYPE_2__* lpVtbl; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* Start ) (TYPE_10__*) ;int /*<<< orphan*/  (* GetService ) (TYPE_10__*,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* GetBufferSize ) (TYPE_10__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Initialize ) (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* GetMixFormat ) (TYPE_10__*,TYPE_8__**) ;} ;
struct TYPE_33__ {char* monitoring_device_id; int /*<<< orphan*/  audio; } ;
struct TYPE_32__ {int /*<<< orphan*/  (* Activate ) (TYPE_17__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;
struct TYPE_31__ {int /*<<< orphan*/  (* GetDevice ) (TYPE_9__*,int /*<<< orphan*/ *,TYPE_17__**) ;int /*<<< orphan*/  (* GetDefaultAudioEndpoint ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_17__**) ;} ;
struct TYPE_30__ {TYPE_4__ audio; } ;
struct TYPE_28__ {TYPE_3__* lpVtbl; } ;
struct TYPE_27__ {TYPE_5__* lpVtbl; } ;
typedef  TYPE_9__ IMMDeviceEnumerator ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  AUDIO_FORMAT_FLOAT ; 
 int /*<<< orphan*/  AUDIO_FORMAT_FLOAT_PLANAR ; 
 int /*<<< orphan*/  CLSCTX_ALL ; 
 int /*<<< orphan*/  CLSID_MMDeviceEnumerator ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_8__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IAudioClient ; 
 int /*<<< orphan*/  IID_IAudioRenderClient ; 
 int /*<<< orphan*/  IID_IMMDeviceEnumerator ; 
 int OBS_SOURCE_DO_NOT_SELF_MONITOR ; 
 struct audio_output_info* audio_output_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_resampler_create (struct resample_info*,struct resample_info*) ; 
 int /*<<< orphan*/  convert_speaker_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devices_match (char const*,char const*) ; 
 int /*<<< orphan*/  eConsole ; 
 int /*<<< orphan*/  eRender ; 
 TYPE_24__* obs ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_source_get_settings (TYPE_6__*) ; 
 int /*<<< orphan*/  os_utf8_to_wcs (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_release (TYPE_9__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_17__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__*,int /*<<< orphan*/ *,TYPE_17__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_17__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub4 (TYPE_10__*,TYPE_8__**) ; 
 int /*<<< orphan*/  stub5 (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (TYPE_10__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub8 (TYPE_10__*) ; 

__attribute__((used)) static bool audio_monitor_init(struct audio_monitor *monitor,
		obs_source_t *source)
{
	IMMDeviceEnumerator *immde = NULL;
	WAVEFORMATEX *wfex = NULL;
	bool success = false;
	UINT32 frames;
	HRESULT hr;

	pthread_mutex_init_value(&monitor->playback_mutex);

	monitor->source = source;

	const char *id = obs->audio.monitoring_device_id;
	if (!id) {
		return false;
	}

	if (source->info.output_flags & OBS_SOURCE_DO_NOT_SELF_MONITOR) {
		obs_data_t *s = obs_source_get_settings(source);
		const char *s_dev_id = obs_data_get_string(s, "device_id");
		bool match = devices_match(s_dev_id, id);
		obs_data_release(s);

		if (match) {
			monitor->ignore = true;
			return true;
		}
	}

	/* ------------------------------------------ *
	 * Init device                                */

	hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL,
			&IID_IMMDeviceEnumerator, (void**)&immde);
	if (FAILED(hr)) {
		return false;
	}

	if (strcmp(id, "default") == 0) {
		hr = immde->lpVtbl->GetDefaultAudioEndpoint(immde,
				eRender, eConsole, &monitor->device);
	} else {
		wchar_t w_id[512];
		os_utf8_to_wcs(id, 0, w_id, 512);

		hr = immde->lpVtbl->GetDevice(immde, w_id, &monitor->device);
	}

	if (FAILED(hr)) {
		goto fail;
	}

	/* ------------------------------------------ *
	 * Init client                                */

	hr = monitor->device->lpVtbl->Activate(monitor->device,
			&IID_IAudioClient, CLSCTX_ALL, NULL,
			(void**)&monitor->client);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = monitor->client->lpVtbl->GetMixFormat(monitor->client, &wfex);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = monitor->client->lpVtbl->Initialize(monitor->client,
			AUDCLNT_SHAREMODE_SHARED, 0,
			10000000, 0, wfex, NULL);
	if (FAILED(hr)) {
		goto fail;
	}

	/* ------------------------------------------ *
	 * Init resampler                             */

	const struct audio_output_info *info = audio_output_get_info(
			obs->audio.audio);
	WAVEFORMATEXTENSIBLE *ext = (WAVEFORMATEXTENSIBLE*)wfex;
	struct resample_info from;
	struct resample_info to;

	from.samples_per_sec = info->samples_per_sec;
	from.speakers = info->speakers;
	from.format = AUDIO_FORMAT_FLOAT_PLANAR;

	to.samples_per_sec = (uint32_t)wfex->nSamplesPerSec;
	to.speakers = convert_speaker_layout(ext->dwChannelMask,
			wfex->nChannels);
	to.format = AUDIO_FORMAT_FLOAT;

	monitor->sample_rate = (uint32_t)wfex->nSamplesPerSec;
	monitor->channels = wfex->nChannels;
	monitor->resampler = audio_resampler_create(&to, &from);
	if (!monitor->resampler) {
		goto fail;
	}

	/* ------------------------------------------ *
	 * Init client                                */

	hr = monitor->client->lpVtbl->GetBufferSize(monitor->client, &frames);
	if (FAILED(hr)) {
		goto fail;
	}

	hr = monitor->client->lpVtbl->GetService(monitor->client,
			&IID_IAudioRenderClient, (void**)&monitor->render);
	if (FAILED(hr)) {
		goto fail;
	}

	if (pthread_mutex_init(&monitor->playback_mutex, NULL) != 0) {
		goto fail;
	}

	hr = monitor->client->lpVtbl->Start(monitor->client);
	if (FAILED(hr)) {
		goto fail;
	}

	success = true;

fail:
	safe_release(immde);
	if (wfex)
		CoTaskMemFree(wfex);
	return success;
}