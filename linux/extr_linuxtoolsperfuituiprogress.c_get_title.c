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
struct ui_progress {int /*<<< orphan*/  title; int /*<<< orphan*/  total; int /*<<< orphan*/  curr; } ;
typedef  int /*<<< orphan*/  buf_tot ;
typedef  int /*<<< orphan*/  buf_cur ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int unit_number__scnprintf (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_title(struct ui_progress *p, char *buf, size_t size)
{
	char buf_cur[20];
	char buf_tot[20];
	int ret;

	ret  = unit_number__scnprintf(buf_cur, sizeof(buf_cur), p->curr);
	ret += unit_number__scnprintf(buf_tot, sizeof(buf_tot), p->total);

	return ret + scnprintf(buf, size, "%s [%s/%s]",
			       p->title, buf_cur, buf_tot);
}