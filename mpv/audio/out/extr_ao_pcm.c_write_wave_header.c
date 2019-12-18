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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int num; } ;
struct ao {scalar_t__ format; int samplerate; int bps; TYPE_1__ channels; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AF_FORMAT_FLOAT ; 
 int WAV_ID_DATA ; 
 int WAV_ID_FLOAT_PCM ; 
 int WAV_ID_FMT ; 
 int WAV_ID_FORMAT_EXTENSIBLE ; 
 int WAV_ID_PCM ; 
 int WAV_ID_RIFF ; 
 int WAV_ID_WAVE ; 
 int af_fmt_to_bytes (scalar_t__) ; 
 int /*<<< orphan*/  fput16le (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput32le (int,int /*<<< orphan*/ *) ; 
 int mp_chmap_to_waveext (TYPE_1__*) ; 

__attribute__((used)) static void write_wave_header(struct ao *ao, FILE *fp, uint64_t data_length)
{
    uint16_t fmt = ao->format == AF_FORMAT_FLOAT ? WAV_ID_FLOAT_PCM : WAV_ID_PCM;
    int bits = af_fmt_to_bytes(ao->format) * 8;

    // Master RIFF chunk
    fput32le(WAV_ID_RIFF, fp);
    // RIFF chunk size: 'WAVE' + 'fmt ' + 4 + 40 +
    // data chunk hdr (8) + data length
    fput32le(12 + 40 + 8 + data_length, fp);
    fput32le(WAV_ID_WAVE, fp);

    // Format chunk
    fput32le(WAV_ID_FMT, fp);
    fput32le(40, fp);
    fput16le(WAV_ID_FORMAT_EXTENSIBLE, fp);
    fput16le(ao->channels.num, fp);
    fput32le(ao->samplerate, fp);
    fput32le(ao->bps, fp);
    fput16le(ao->channels.num * (bits / 8), fp);
    fput16le(bits, fp);

    // Extension chunk
    fput16le(22, fp);
    fput16le(bits, fp);
    fput32le(mp_chmap_to_waveext(&ao->channels), fp);
    // 2 bytes format + 14 bytes guid
    fput32le(fmt, fp);
    fput32le(0x00100000, fp);
    fput32le(0xAA000080, fp);
    fput32le(0x719B3800, fp);

    // Data chunk
    fput32le(WAV_ID_DATA, fp);
    fput32le(data_length, fp);
}