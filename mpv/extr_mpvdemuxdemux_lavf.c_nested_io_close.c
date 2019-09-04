#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demuxer {TYPE_1__* priv; } ;
struct AVFormatContext {struct demuxer* opaque; } ;
struct TYPE_3__ {int num_nested; int /*<<< orphan*/  (* default_io_close ) (struct AVFormatContext*,int /*<<< orphan*/ *) ;TYPE_2__* nested; } ;
typedef  TYPE_1__ lavf_priv_t ;
struct TYPE_4__ {int /*<<< orphan*/ * id; } ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct AVFormatContext*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nested_io_close(struct AVFormatContext *s, AVIOContext *pb)
{
    struct demuxer *demuxer = s->opaque;
    lavf_priv_t *priv = demuxer->priv;

    for (int n = 0; n < priv->num_nested; n++) {
        if (priv->nested[n].id == pb) {
            MP_TARRAY_REMOVE_AT(priv->nested, priv->num_nested, n);
            break;
        }
    }


    priv->default_io_close(s, pb);
}