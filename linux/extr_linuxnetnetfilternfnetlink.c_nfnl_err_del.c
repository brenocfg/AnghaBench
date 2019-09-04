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
struct nfnl_err {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfnl_err*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfnl_err_del(struct nfnl_err *nfnl_err)
{
	list_del(&nfnl_err->head);
	kfree(nfnl_err);
}