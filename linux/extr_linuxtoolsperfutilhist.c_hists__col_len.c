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
typedef  int /*<<< orphan*/  u16 ;
struct hists {int /*<<< orphan*/ * col_len; } ;
typedef  enum hist_column { ____Placeholder_hist_column } hist_column ;

/* Variables and functions */

u16 hists__col_len(struct hists *hists, enum hist_column col)
{
	return hists->col_len[col];
}