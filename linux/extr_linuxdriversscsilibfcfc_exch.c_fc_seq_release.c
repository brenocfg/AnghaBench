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
struct fc_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_exch_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_seq_exch (struct fc_seq*) ; 

void fc_seq_release(struct fc_seq *sp)
{
	fc_exch_release(fc_seq_exch(sp));
}