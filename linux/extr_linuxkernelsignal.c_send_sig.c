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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __si_special (int) ; 
 int send_sig_info (int,int /*<<< orphan*/ ,struct task_struct*) ; 

int
send_sig(int sig, struct task_struct *p, int priv)
{
	return send_sig_info(sig, __si_special(priv), p);
}