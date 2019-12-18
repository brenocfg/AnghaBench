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
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dlm_reco_unlock_ast(void *astdata, enum dlm_status st)
{
	mlog(0, "unlockast for recovery lock fired!\n");
}