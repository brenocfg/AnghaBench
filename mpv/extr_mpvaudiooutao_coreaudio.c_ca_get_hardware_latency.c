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
typedef  double uint64_t ;
typedef  int uint32_t ;
struct priv {int /*<<< orphan*/  device; int /*<<< orphan*/  audio_unit; } ;
struct ao {struct priv* priv; } ;
typedef  double int64_t ;
typedef  int /*<<< orphan*/  audiounit_latency_sec ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioUnitGetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,int*) ; 
 int /*<<< orphan*/  CHECK_CA_ERROR (char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,double) ; 
 double ca_get_device_latency_us (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioUnitProperty_Latency ; 
 int /*<<< orphan*/  kAudioUnitScope_Global ; 

__attribute__((used)) static int64_t ca_get_hardware_latency(struct ao *ao) {
    struct priv *p = ao->priv;

    double audiounit_latency_sec = 0.0;
    uint32_t size = sizeof(audiounit_latency_sec);
    OSStatus err = AudioUnitGetProperty(
            p->audio_unit,
            kAudioUnitProperty_Latency,
            kAudioUnitScope_Global,
            0,
            &audiounit_latency_sec,
            &size);
    CHECK_CA_ERROR("cannot get audio unit latency");

    uint64_t audiounit_latency_us = audiounit_latency_sec * 1e6;
    uint64_t device_latency_us    = ca_get_device_latency_us(ao, p->device);

    MP_VERBOSE(ao, "audiounit latency [us]: %lld\n", audiounit_latency_us);
    MP_VERBOSE(ao, "device latency [us]: %lld\n", device_latency_us);

    return audiounit_latency_us + device_latency_us;

coreaudio_error:
    return 0;
}