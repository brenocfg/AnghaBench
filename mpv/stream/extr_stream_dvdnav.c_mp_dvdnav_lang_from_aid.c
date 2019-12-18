#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct priv {int /*<<< orphan*/  dvdnav; } ;
struct TYPE_3__ {struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int dvdnav_audio_stream_to_lang (int /*<<< orphan*/ ,int) ; 
 int dvdnav_get_audio_logical_stream (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mp_dvdnav_lang_from_aid(stream_t *stream, int aid)
{
    uint8_t lg;
    uint16_t lang;
    struct priv *priv = stream->priv;

    if (aid < 0)
        return 0;
    lg = dvdnav_get_audio_logical_stream(priv->dvdnav, aid & 0x7);
    if (lg == 0xff)
        return 0;
    lang = dvdnav_audio_stream_to_lang(priv->dvdnav, lg);
    if (lang == 0xffff)
        return 0;
    return lang;
}