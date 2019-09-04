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
 int /*<<< orphan*/ * i2400m_barker_db ; 
 scalar_t__ i2400m_barker_db_size ; 
 scalar_t__ i2400m_barker_db_used ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void i2400m_barker_db_exit(void)
{
	kfree(i2400m_barker_db);
	i2400m_barker_db = NULL;
	i2400m_barker_db_size = 0;
	i2400m_barker_db_used = 0;
}