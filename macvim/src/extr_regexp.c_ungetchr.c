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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  at_start ; 
 int /*<<< orphan*/  curchr ; 
 int /*<<< orphan*/  nextchr ; 
 int /*<<< orphan*/  prev_at_start ; 
 int /*<<< orphan*/  prevchr ; 
 scalar_t__ prevchr_len ; 
 int /*<<< orphan*/  prevprevchr ; 
 int /*<<< orphan*/  regparse ; 

__attribute__((used)) static void
ungetchr()
{
    nextchr = curchr;
    curchr = prevchr;
    prevchr = prevprevchr;
    at_start = prev_at_start;
    prev_at_start = FALSE;

    /* Backup regparse, so that it's at the same position as before the
     * getchr(). */
    regparse -= prevchr_len;
}