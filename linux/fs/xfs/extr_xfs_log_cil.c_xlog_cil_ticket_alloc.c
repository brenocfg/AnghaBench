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
struct xlog_ticket {scalar_t__ t_curr_res; } ;
struct xlog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  XFS_TRANSACTION ; 
 struct xlog_ticket* xlog_ticket_alloc (struct xlog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xlog_ticket *
xlog_cil_ticket_alloc(
	struct xlog	*log)
{
	struct xlog_ticket *tic;

	tic = xlog_ticket_alloc(log, 0, 1, XFS_TRANSACTION, 0,
				KM_NOFS);

	/*
	 * set the current reservation to zero so we know to steal the basic
	 * transaction overhead reservation from the first transaction commit.
	 */
	tic->t_curr_res = 0;
	return tic;
}