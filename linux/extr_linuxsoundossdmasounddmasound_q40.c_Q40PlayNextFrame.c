#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_char ;
struct TYPE_6__ {scalar_t__ stereo; } ;
struct TYPE_5__ {int speed; } ;
struct TYPE_8__ {TYPE_2__ soft; TYPE_1__ hard; } ;
struct TYPE_7__ {int** buffers; size_t front; int count; int max_count; int /*<<< orphan*/  active; int /*<<< orphan*/  block_size; int /*<<< orphan*/  rear_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q40Interrupt ; 
 int /*<<< orphan*/  Q40MonoInterrupt ; 
 int /*<<< orphan*/  Q40StereoInterrupt ; 
 int /*<<< orphan*/  Q40_IRQ_SAMPLE ; 
 int /*<<< orphan*/  SAMPLE_CLEAR_REG ; 
 int /*<<< orphan*/  SAMPLE_ENABLE_REG ; 
 int /*<<< orphan*/  SAMPLE_RATE_REG ; 
 TYPE_4__ dmasound ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ printk_ratelimit () ; 
 int* q40_pp ; 
 int /*<<< orphan*/  q40_sc ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ write_sq ; 

__attribute__((used)) static void Q40PlayNextFrame(int index)
{
	u_char *start;
	u_long size;
	u_char speed;
	int error;

	/* used by Q40Play() if all doubts whether there really is something
	 * to be played are already wiped out.
	 */
	start = write_sq.buffers[write_sq.front];
	size = (write_sq.count == index ? write_sq.rear_size : write_sq.block_size);

	q40_pp=start;
	q40_sc=size;

	write_sq.front = (write_sq.front+1) % write_sq.max_count;
	write_sq.active++;

	speed=(dmasound.hard.speed==10000 ? 0 : 1);

	master_outb( 0,SAMPLE_ENABLE_REG);
	free_irq(Q40_IRQ_SAMPLE, Q40Interrupt);
	if (dmasound.soft.stereo)
		error = request_irq(Q40_IRQ_SAMPLE, Q40StereoInterrupt, 0,
				    "Q40 sound", Q40Interrupt);
	  else
		error = request_irq(Q40_IRQ_SAMPLE, Q40MonoInterrupt, 0,
				    "Q40 sound", Q40Interrupt);
	if (error && printk_ratelimit())
		pr_err("Couldn't register sound interrupt\n");

	master_outb( speed, SAMPLE_RATE_REG);
	master_outb( 1,SAMPLE_CLEAR_REG);
	master_outb( 1,SAMPLE_ENABLE_REG);
}