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

/* Variables and functions */
 int /*<<< orphan*/  AA_FIRST_SECID ; 
 int /*<<< orphan*/  aa_secids ; 
 int /*<<< orphan*/  idr_init_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void aa_secids_init(void)
{
	idr_init_base(&aa_secids, AA_FIRST_SECID);
}