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
struct tty3270_line {int len; int /*<<< orphan*/ * cells; } ;
struct tty3270 {int cy; int cx; struct tty3270_line* screen; } ;

/* Variables and functions */

__attribute__((used)) static void
tty3270_delete_characters(struct tty3270 *tp, int n)
{
	struct tty3270_line *line;
	int i;

	line = tp->screen + tp->cy;
	if (line->len <= tp->cx)
		return;
	if (line->len - tp->cx <= n) {
		line->len = tp->cx;
		return;
	}
	for (i = tp->cx; i + n < line->len; i++)
		line->cells[i] = line->cells[i + n];
	line->len -= n;
}