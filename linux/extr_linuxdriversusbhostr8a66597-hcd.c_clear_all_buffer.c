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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ pipenum; } ;
struct r8a66597_pipe {int /*<<< orphan*/  pipectr; TYPE_1__ info; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLRM ; 
 int /*<<< orphan*/  pipe_stop (struct r8a66597*,struct r8a66597_pipe*) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_read (struct r8a66597*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_all_buffer(struct r8a66597 *r8a66597,
			     struct r8a66597_pipe *pipe)
{
	u16 tmp;

	if (!pipe || pipe->info.pipenum == 0)
		return;

	pipe_stop(r8a66597, pipe);
	r8a66597_bset(r8a66597, ACLRM, pipe->pipectr);
	tmp = r8a66597_read(r8a66597, pipe->pipectr);
	tmp = r8a66597_read(r8a66597, pipe->pipectr);
	tmp = r8a66597_read(r8a66597, pipe->pipectr);
	r8a66597_bclr(r8a66597, ACLRM, pipe->pipectr);
}