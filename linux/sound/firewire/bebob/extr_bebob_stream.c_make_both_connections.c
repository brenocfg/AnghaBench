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
struct snd_bebob {int /*<<< orphan*/  out_conn; int /*<<< orphan*/  in_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_connection_break (int /*<<< orphan*/ *) ; 
 int cmp_connection_establish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int make_both_connections(struct snd_bebob *bebob)
{
	int err = 0;

	err = cmp_connection_establish(&bebob->out_conn);
	if (err < 0)
		return err;

	err = cmp_connection_establish(&bebob->in_conn);
	if (err < 0) {
		cmp_connection_break(&bebob->out_conn);
		return err;
	}

	return 0;
}