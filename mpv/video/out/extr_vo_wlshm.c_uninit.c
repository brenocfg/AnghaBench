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
struct priv {struct buffer* free_buffers; } ;
struct buffer {struct buffer* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (struct buffer*) ; 
 int /*<<< orphan*/  vo_wayland_uninit (struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct priv *p = vo->priv;
    struct buffer *buf;

    while (p->free_buffers) {
        buf = p->free_buffers;
        p->free_buffers = buf->next;
        talloc_free(buf);
    }
    vo_wayland_uninit(vo);
}