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
struct strparser {scalar_t__ need_bytes; scalar_t__ paused; } ;

/* Variables and functions */
 scalar_t__ strp_peek_len (struct strparser*) ; 
 int /*<<< orphan*/  strp_read_sock (struct strparser*) ; 

void __strp_unpause(struct strparser *strp)
{
	strp->paused = 0;

	if (strp->need_bytes) {
		if (strp_peek_len(strp) < strp->need_bytes)
			return;
	}
	strp_read_sock(strp);
}