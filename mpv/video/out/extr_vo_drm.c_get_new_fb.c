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
struct vo {struct priv* priv; } ;
struct priv {size_t front_buf; size_t buf_count; struct framebuffer* bufs; } ;
struct framebuffer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct framebuffer *get_new_fb(struct vo *vo)
{
    struct priv *p = vo->priv;

    p->front_buf++;
    p->front_buf %= p->buf_count;

    return &p->bufs[p->front_buf];
}