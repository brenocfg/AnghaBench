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
struct tty_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* speakup_tty ; 
 int /*<<< orphan*/  speakup_tty_mutex ; 

__attribute__((used)) static void spk_ttyio_ldisc_close(struct tty_struct *tty)
{
	mutex_lock(&speakup_tty_mutex);
	kfree(speakup_tty->disc_data);
	speakup_tty = NULL;
	mutex_unlock(&speakup_tty_mutex);
}