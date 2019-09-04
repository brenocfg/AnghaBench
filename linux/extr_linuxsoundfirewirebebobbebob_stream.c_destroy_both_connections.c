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
 int /*<<< orphan*/  cmp_connection_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
destroy_both_connections(struct snd_bebob *bebob)
{
	cmp_connection_destroy(&bebob->in_conn);
	cmp_connection_destroy(&bebob->out_conn);
}