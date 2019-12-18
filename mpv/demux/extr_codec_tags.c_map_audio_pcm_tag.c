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
typedef  void* uint64_t ;
struct mp_chmap {scalar_t__ num; } ;
struct mp_codec_params {int codec_tag; int extradata_size; unsigned char* extradata; int bits_per_coded_sample; int /*<<< orphan*/  type; int /*<<< orphan*/  codec; struct mp_chmap channels; } ;

/* Variables and functions */
 void* AV_RL32 (unsigned char*) ; 
 scalar_t__ guid_ext_base ; 
 int /*<<< orphan*/  lookup_tag (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  mp_chmap_from_waveext (struct mp_chmap*,void*) ; 
 int /*<<< orphan*/  mp_set_pcm_codec (struct mp_codec_params*,int,int,int,int) ; 

__attribute__((used)) static void map_audio_pcm_tag(struct mp_codec_params *c)
{
    // MS PCM, Extended
    if (c->codec_tag == 0xfffe && c->extradata_size >= 22) {
        // WAVEFORMATEXTENSIBLE.dwChannelMask
        uint64_t chmask = AV_RL32(c->extradata + 2);
        struct mp_chmap chmap;
        mp_chmap_from_waveext(&chmap, chmask);
        if (c->channels.num == chmap.num)
            c->channels = chmap;

        // WAVEFORMATEXTENSIBLE.SubFormat
        unsigned char *subformat = c->extradata + 6;
        if (memcmp(subformat + 4, guid_ext_base + 4, 12) == 0) {
            c->codec_tag = AV_RL32(subformat);
            c->codec = lookup_tag(c->type, c->codec_tag);
        }

        // Compressed formats might use this.
        c->extradata += 22;
        c->extradata_size -= 22;
    }

    int bits = c->bits_per_coded_sample;
    int bytes = (bits + 7) / 8;
    switch (c->codec_tag) {
    case 0x0:       // Microsoft PCM
    case 0x1:
        if (bytes >= 1 && bytes <= 4)
            mp_set_pcm_codec(c, bytes > 1, false, bytes * 8, false);
        break;
    case 0x3:       // IEEE float
        mp_set_pcm_codec(c, true, true, bits == 64 ? 64 : 32, false);
        break;
    }
}