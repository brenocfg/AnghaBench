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
struct ao {int dummy; } ;
typedef  scalar_t__ ALint ;

/* Variables and functions */
 scalar_t__ AL_PLAYING ; 
 int /*<<< orphan*/  AL_SOURCE_STATE ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mp_sleep_us (int) ; 
 int /*<<< orphan*/  source ; 

__attribute__((used)) static void drain(struct ao *ao)
{
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    while (state == AL_PLAYING) {
        mp_sleep_us(10000);
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }
}