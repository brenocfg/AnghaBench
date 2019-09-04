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
typedef  int /*<<< orphan*/  dtd ;
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  int /*<<< orphan*/  DTableDesc ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static DTableDesc HUF_getDTableDesc(const HUF_DTable *table)
{
	DTableDesc dtd;
	memcpy(&dtd, table, sizeof(dtd));
	return dtd;
}