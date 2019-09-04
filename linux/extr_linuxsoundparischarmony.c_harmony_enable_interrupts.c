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
typedef  int /*<<< orphan*/  u32 ;
struct snd_harmony {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARMONY_DSTATUS ; 
 int /*<<< orphan*/  HARMONY_DSTATUS_IE ; 
 int /*<<< orphan*/  harmony_read (struct snd_harmony*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  harmony_wait_for_control (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_write (struct snd_harmony*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
harmony_enable_interrupts(struct snd_harmony *h)
{
	u32 dstatus;
	harmony_wait_for_control(h);
	dstatus = harmony_read(h, HARMONY_DSTATUS);
	dstatus |= HARMONY_DSTATUS_IE;
	harmony_write(h, HARMONY_DSTATUS, dstatus);
}