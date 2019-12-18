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
struct mp_recorder_sink {int dummy; } ;
struct mp_recorder {int num_streams; TYPE_1__* mux; struct mp_recorder_sink** streams; scalar_t__ opened; } ;
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_recorder*,char*) ; 
 scalar_t__ av_write_trailer (TYPE_1__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_1__*) ; 
 scalar_t__ avio_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_packets (struct mp_recorder*) ; 
 int /*<<< orphan*/  mux_packets (struct mp_recorder_sink*,int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_recorder*) ; 

void mp_recorder_destroy(struct mp_recorder *priv)
{
    if (priv->opened) {
        for (int n = 0; n < priv->num_streams; n++) {
            struct mp_recorder_sink *rst = priv->streams[n];
            mux_packets(rst, true);
        }

        if (av_write_trailer(priv->mux) < 0)
            MP_ERR(priv, "Writing trailer failed.\n");
    }

    if (priv->mux) {
        if (avio_closep(&priv->mux->pb) < 0)
            MP_ERR(priv, "Closing file failed\n");

        avformat_free_context(priv->mux);
    }

    flush_packets(priv);
    talloc_free(priv);
}