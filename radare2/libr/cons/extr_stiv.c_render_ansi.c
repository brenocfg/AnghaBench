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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  (* PrintfCallback ) (char*,int) ;

/* Variables and functions */
 int reduce8 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void render_ansi(PrintfCallback cb_printf, const ut8 *c, const ut8 *d) {
	int fg = 0;
	int color = reduce8 (c[0], c[1], c[2]);
	if (color == -1)return;
	//if (c[0]<30 && c[1]<30 && c[2]<30) fg = 1;
	cb_printf ("\x1b[%dm", color+(fg?30:40));
}