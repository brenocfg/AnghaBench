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
struct nested_stream {int /*<<< orphan*/ * id; } ;
struct demuxer {TYPE_1__* priv; } ;
struct AVFormatContext {struct demuxer* opaque; } ;
struct TYPE_3__ {int (* default_io_open ) (struct AVFormatContext*,int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ **) ;int /*<<< orphan*/  num_nested; int /*<<< orphan*/  nested; } ;
typedef  TYPE_1__ lavf_priv_t ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nested_stream) ; 
 int stub1 (struct AVFormatContext*,int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int nested_io_open(struct AVFormatContext *s, AVIOContext **pb,
                          const char *url, int flags, AVDictionary **options)
{
    struct demuxer *demuxer = s->opaque;
    lavf_priv_t *priv = demuxer->priv;

    int r = priv->default_io_open(s, pb, url, flags, options);
    if (r >= 0) {
        struct nested_stream nest = {
            .id = *pb,
        };
        MP_TARRAY_APPEND(priv, priv->nested, priv->num_nested, nest);
    }
    return r;
}