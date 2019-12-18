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
struct vo_chain {int underrun; int /*<<< orphan*/  vo; } ;

/* Variables and functions */
 int /*<<< orphan*/  vo_seek_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vo_chain_reset_state(struct vo_chain *vo_c)
{
    vo_seek_reset(vo_c->vo);
    vo_c->underrun = false;
}