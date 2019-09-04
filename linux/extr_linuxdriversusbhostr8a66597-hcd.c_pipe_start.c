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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ pipenum; } ;
struct r8a66597_pipe {int /*<<< orphan*/  pipectr; TYPE_1__ info; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int PID ; 
 int /*<<< orphan*/  PID_BUF ; 
 int /*<<< orphan*/  PID_NAK ; 
 int PID_STALL ; 
 int /*<<< orphan*/  r8a66597_mdfy (struct r8a66597*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int r8a66597_read (struct r8a66597*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_start(struct r8a66597 *r8a66597, struct r8a66597_pipe *pipe)
{
	u16 tmp;

	tmp = r8a66597_read(r8a66597, pipe->pipectr) & PID;
	if ((pipe->info.pipenum != 0) & ((tmp & PID_STALL) != 0)) /* stall? */
		r8a66597_mdfy(r8a66597, PID_NAK, PID, pipe->pipectr);
	r8a66597_mdfy(r8a66597, PID_BUF, PID, pipe->pipectr);
}