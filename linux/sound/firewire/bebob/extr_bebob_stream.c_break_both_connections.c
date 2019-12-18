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
struct snd_bebob {int /*<<< orphan*/ * maudio_special_quirk; int /*<<< orphan*/  out_conn; int /*<<< orphan*/  in_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void
break_both_connections(struct snd_bebob *bebob)
{
	cmp_connection_break(&bebob->in_conn);
	cmp_connection_break(&bebob->out_conn);

	/* These models seems to be in transition state for a longer time. */
	if (bebob->maudio_special_quirk != NULL)
		msleep(200);
}