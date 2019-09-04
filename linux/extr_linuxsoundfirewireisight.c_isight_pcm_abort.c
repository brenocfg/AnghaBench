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
struct isight {int /*<<< orphan*/  pcm; int /*<<< orphan*/  pcm_active; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isight_pcm_abort(struct isight *isight)
{
	if (READ_ONCE(isight->pcm_active))
		snd_pcm_stop_xrun(isight->pcm);
}