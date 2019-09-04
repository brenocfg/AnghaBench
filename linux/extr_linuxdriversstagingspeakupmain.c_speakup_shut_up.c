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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  speakup_date (struct vc_data*) ; 
 int /*<<< orphan*/  spk_do_flush () ; 
 scalar_t__ spk_killed ; 
 int spk_parked ; 
 int spk_shut_up ; 
 scalar_t__ synth ; 

__attribute__((used)) static void speakup_shut_up(struct vc_data *vc)
{
	if (spk_killed)
		return;
	spk_shut_up |= 0x01;
	spk_parked &= 0xfe;
	speakup_date(vc);
	if (synth)
		spk_do_flush();
}