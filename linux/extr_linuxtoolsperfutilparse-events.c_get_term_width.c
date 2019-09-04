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
struct winsize {scalar_t__ ws_col; } ;

/* Variables and functions */
 scalar_t__ MAX_WIDTH ; 
 int /*<<< orphan*/  get_term_dimensions (struct winsize*) ; 

__attribute__((used)) static int get_term_width(void)
{
	struct winsize ws;

	get_term_dimensions(&ws);
	return ws.ws_col > MAX_WIDTH ? MAX_WIDTH : ws.ws_col;
}