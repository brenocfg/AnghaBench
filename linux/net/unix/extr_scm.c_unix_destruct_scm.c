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
struct sk_buff {int dummy; } ;
struct scm_cookie {int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  scm ;
struct TYPE_2__ {scalar_t__ fp; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__ UNIXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct scm_cookie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scm_destroy (struct scm_cookie*) ; 
 int /*<<< orphan*/  sock_wfree (struct sk_buff*) ; 
 int /*<<< orphan*/  unix_detach_fds (struct scm_cookie*,struct sk_buff*) ; 

void unix_destruct_scm(struct sk_buff *skb)
{
	struct scm_cookie scm;

	memset(&scm, 0, sizeof(scm));
	scm.pid  = UNIXCB(skb).pid;
	if (UNIXCB(skb).fp)
		unix_detach_fds(&scm, skb);

	/* Alas, it calls VFS */
	/* So fscking what? fput() had been SMP-safe since the last Summer */
	scm_destroy(&scm);
	sock_wfree(skb);
}