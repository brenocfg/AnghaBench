#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spk_synth {int /*<<< orphan*/  (* synth_immediate ) (struct spk_synth*,char*) ;TYPE_1__* io_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_buffer ) () ;} ;

/* Variables and functions */
 scalar_t__ in_escape ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct spk_synth*,char*) ; 

__attribute__((used)) static void synth_flush(struct spk_synth *synth)
{
	in_escape = 0;
	synth->io_ops->flush_buffer();
	synth->synth_immediate(synth, "\033P;10z\033\\");
}