#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int sizeimage; } ;
struct TYPE_10__ {TYPE_2__ pix; } ;
struct TYPE_9__ {TYPE_4__ fmt; } ;
struct TYPE_11__ {TYPE_3__ format; TYPE_1__* tv_param; } ;
typedef  TYPE_5__ priv_t ;
struct TYPE_7__ {int buffer_size; } ;

/* Variables and functions */

__attribute__((used)) static int get_capture_buffer_size(priv_t *priv)
{
    uint64_t bufsize;
    int cnt;

    if (priv->tv_param->buffer_size >= 0) {
        bufsize = priv->tv_param->buffer_size*1024*1024;
    } else {
        bufsize = 16*1024*1024;
    }

    cnt = bufsize/priv->format.fmt.pix.sizeimage;
    if (cnt < 2) cnt = 2;

    return cnt;
}