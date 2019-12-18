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
typedef  int /*<<< orphan*/  (* PrintfCallback ) (char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ;

/* Variables and functions */

__attribute__((used)) static void render_rgb(PrintfCallback cb_printf, const ut8 *c, const ut8 *d) {
	cb_printf ("\x1b[38;2;%d;%d;%dm", c[0], c[1], c[2]);
	cb_printf ("\x1b[48;2;%d;%d;%dm", d[0], d[1], d[2]);
}