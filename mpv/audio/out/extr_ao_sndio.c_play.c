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
struct priv {int delay; int playing; int /*<<< orphan*/  hdl; } ;
struct ao {int sstride; struct priv* priv; } ;

/* Variables and functions */
 int sio_write (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int play(struct ao *ao, void **data, int samples, int flags)
{
    struct priv *p = ao->priv;
    int n;

    n = sio_write(p->hdl, data[0], samples * ao->sstride) / ao->sstride;
    p->delay += n;
    p->playing = true;
    /* on AOPLAY_FINAL_CHUNK, just let it underrun */
    return n;
}