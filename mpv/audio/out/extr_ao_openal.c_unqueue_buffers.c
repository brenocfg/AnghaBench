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
struct priv {int num_buffers; } ;
struct ao {struct priv* priv; } ;
typedef  int ALint ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BUFFERS_PROCESSED ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  alSourceUnqueueBuffers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * buffers ; 
 int /*<<< orphan*/  source ; 
 size_t unqueue_buf ; 

__attribute__((used)) static void unqueue_buffers(struct ao *ao)
{
    struct priv *q = ao->priv;
    ALint p;
    int till_wrap = q->num_buffers - unqueue_buf;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &p);
    if (p >= till_wrap) {
        alSourceUnqueueBuffers(source, till_wrap, &buffers[unqueue_buf]);
        unqueue_buf = 0;
        p -= till_wrap;
    }
    if (p) {
        alSourceUnqueueBuffers(source, p, &buffers[unqueue_buf]);
        unqueue_buf += p;
    }
}