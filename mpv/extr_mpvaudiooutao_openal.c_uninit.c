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
struct priv {int /*<<< orphan*/  num_buffers; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  ALCdevice ;
typedef  int /*<<< orphan*/  ALCcontext ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BUFFER ; 
 int /*<<< orphan*/  alDeleteBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alDeleteSources (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alSourceStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCloseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcDestroyContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcGetContextsDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alcGetCurrentContext () ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ao_data ; 
 int /*<<< orphan*/  buffers ; 
 int /*<<< orphan*/  source ; 

__attribute__((used)) static void uninit(struct ao *ao)
{
    struct priv *p = ao->priv;
    alSourceStop(source);
    alSourcei(source, AL_BUFFER, 0);

    alDeleteBuffers(p->num_buffers, buffers);
    alDeleteSources(1, &source);

    ALCcontext *ctx = alcGetCurrentContext();
    ALCdevice *dev = alcGetContextsDevice(ctx);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
    ao_data = NULL;
}