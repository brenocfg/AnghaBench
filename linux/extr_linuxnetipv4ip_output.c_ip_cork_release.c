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
struct inet_cork {int /*<<< orphan*/ * dst; int /*<<< orphan*/ * opt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCORK_OPT ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip_cork_release(struct inet_cork *cork)
{
	cork->flags &= ~IPCORK_OPT;
	kfree(cork->opt);
	cork->opt = NULL;
	dst_release(cork->dst);
	cork->dst = NULL;
}