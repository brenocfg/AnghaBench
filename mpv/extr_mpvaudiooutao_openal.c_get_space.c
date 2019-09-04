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
struct priv {int num_buffers; int num_samples; } ;
struct ao {struct priv* priv; } ;
typedef  int ALint ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BUFFERS_QUEUED ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  unqueue_buffers (struct ao*) ; 

__attribute__((used)) static int get_space(struct ao *ao)
{
    struct priv *p = ao->priv;
    ALint queued;
    unqueue_buffers(ao);
    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
    queued = p->num_buffers - queued;
    if (queued < 0)
        return 0;
    return p->num_samples * queued;
}