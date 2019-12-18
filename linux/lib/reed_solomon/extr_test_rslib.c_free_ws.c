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
struct wspace {struct wspace* c; struct wspace* errlocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wspace*) ; 

__attribute__((used)) static void free_ws(struct wspace *ws)
{
	if (!ws)
		return;

	kfree(ws->errlocs);
	kfree(ws->c);
	kfree(ws);
}