#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct vc_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 scalar_t__ MINECHOCHAR ; 
 int /*<<< orphan*/  speak_char (scalar_t__) ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int spk_key_echo ; 
 scalar_t__ spk_keydown ; 
 scalar_t__ spk_killed ; 
 scalar_t__ spk_lastkey ; 
 int spk_parked ; 
 int spk_shut_up ; 
 int /*<<< orphan*/  synth ; 

__attribute__((used)) static void do_handle_latin(struct vc_data *vc, u_char value, char up_flag)
{
	unsigned long flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	if (up_flag) {
		spk_lastkey = 0;
		spk_keydown = 0;
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		return;
	}
	if (!synth || spk_killed) {
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		return;
	}
	spk_shut_up &= 0xfe;
	spk_lastkey = value;
	spk_keydown++;
	spk_parked &= 0xfe;
	if (spk_key_echo == 2 && value >= MINECHOCHAR)
		speak_char(value);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
}