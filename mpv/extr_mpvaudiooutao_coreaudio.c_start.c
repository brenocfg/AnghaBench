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
struct priv {int /*<<< orphan*/  audio_unit; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AudioOutputUnitStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CA_WARN (char*) ; 

__attribute__((used)) static void start(struct ao *ao)
{
    struct priv *p = ao->priv;
    OSStatus err = AudioOutputUnitStart(p->audio_unit);
    CHECK_CA_WARN("can't start audio unit");
}