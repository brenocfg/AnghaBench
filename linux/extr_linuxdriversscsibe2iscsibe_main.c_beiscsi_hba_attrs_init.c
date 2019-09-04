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
struct beiscsi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  beiscsi_log_enable ; 
 int /*<<< orphan*/  beiscsi_log_enable_init (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void beiscsi_hba_attrs_init(struct beiscsi_hba *phba)
{
	/* Set the logging parameter */
	beiscsi_log_enable_init(phba, beiscsi_log_enable);
}