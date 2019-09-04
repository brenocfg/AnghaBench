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
typedef  int /*<<< orphan*/  uint32_t ;
struct dlm_message {int dummy; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _receive_message (struct dlm_ls*,struct dlm_message*,int /*<<< orphan*/ ) ; 

void dlm_receive_message_saved(struct dlm_ls *ls, struct dlm_message *ms,
			       uint32_t saved_seq)
{
	_receive_message(ls, ms, saved_seq);
}