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
typedef  int DWORD ;

/* Variables and functions */

DWORD DSOUND_fraglen(DWORD nSamplesPerSec, DWORD nBlockAlign)
{
    /* Given a timer delay of 10ms, the fragment size is approximately:
     *     fraglen = (nSamplesPerSec * 10 / 1000) * nBlockAlign
     * ==> fraglen = (nSamplesPerSec / 100) * nBlockSize
     *
     * ALSA uses buffers that are powers of 2. Because of this, fraglen
     * is rounded up to the nearest power of 2:
     */

    if (nSamplesPerSec <= 12800)
        return 128 * nBlockAlign;

    if (nSamplesPerSec <= 25600)
        return 256 * nBlockAlign;

    if (nSamplesPerSec <= 51200)
        return 512 * nBlockAlign;

    return 1024 * nBlockAlign;
}