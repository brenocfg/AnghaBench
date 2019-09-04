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
typedef  int u16 ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int BEMPE ; 
 int BRDYE ; 
 unsigned long INTENB0 ; 
 int NRDYE ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int,unsigned long) ; 
 int r8a66597_read (struct r8a66597*,unsigned long) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int,unsigned long) ; 

__attribute__((used)) static void disable_pipe_irq(struct r8a66597 *r8a66597, u16 pipenum,
			     unsigned long reg)
{
	u16 tmp;

	tmp = r8a66597_read(r8a66597, INTENB0);
	r8a66597_bclr(r8a66597, BEMPE | NRDYE | BRDYE, INTENB0);
	r8a66597_bclr(r8a66597, 1 << pipenum, reg);
	r8a66597_write(r8a66597, tmp, INTENB0);
}