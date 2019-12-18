#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_decoder_list {int dummy; } ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_4__ {int type; int /*<<< orphan*/  long_name; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 int AVMEDIA_TYPE_UNKNOWN ; 
 int av_codec_is_decoder (TYPE_1__ const*) ; 
 TYPE_1__* av_codec_iterate (void**) ; 
 int /*<<< orphan*/  mp_add_decoder (struct mp_decoder_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_codec_from_av_codec_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_codecs(struct mp_decoder_list *list, enum AVMediaType type,
                       bool decoders)
{
    void *iter = NULL;
    for (;;) {
        const AVCodec *cur = av_codec_iterate(&iter);
        if (!cur)
            break;
        if (av_codec_is_decoder(cur) == decoders &&
            (type == AVMEDIA_TYPE_UNKNOWN || cur->type == type))
        {
            mp_add_decoder(list, mp_codec_from_av_codec_id(cur->id),
                           cur->name, cur->long_name);
        }
    }
}