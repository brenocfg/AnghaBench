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
struct mp_codec_params {int /*<<< orphan*/  codec; } ;
typedef  int /*<<< orphan*/  codec ;

/* Variables and functions */
 int /*<<< orphan*/  mp_snprintf_cat (char*,int,char*,...) ; 
 int /*<<< orphan*/  talloc_strdup (struct mp_codec_params*,char*) ; 

void mp_set_pcm_codec(struct mp_codec_params *c, bool sign, bool is_float,
                      int bits, bool is_be)
{
    // This uses libavcodec pcm codec names, e.g. "pcm_u16le".
    char codec[64] = "pcm_";
    if (is_float) {
        mp_snprintf_cat(codec, sizeof(codec), "f");
    } else {
        mp_snprintf_cat(codec, sizeof(codec), sign ? "s" : "u");
    }
    mp_snprintf_cat(codec, sizeof(codec), "%d", bits);
    if (bits != 8)
        mp_snprintf_cat(codec, sizeof(codec), is_be ? "be" : "le");
    c->codec = talloc_strdup(c, codec);
}