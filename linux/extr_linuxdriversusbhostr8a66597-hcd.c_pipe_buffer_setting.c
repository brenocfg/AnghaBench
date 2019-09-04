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
struct r8a66597_pipe_info {scalar_t__ pipenum; int type; int epnum; int buf_bsize; int bufnum; int maxpacket; int interval; int /*<<< orphan*/  address; scalar_t__ dir_in; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLRM ; 
 int /*<<< orphan*/  PIPEBUF ; 
 int /*<<< orphan*/  PIPECFG ; 
 int /*<<< orphan*/  PIPEMAXP ; 
 int /*<<< orphan*/  PIPEPERI ; 
 int /*<<< orphan*/  PIPESEL ; 
 int R8A66597_BULK ; 
 int R8A66597_DBLB ; 
 int R8A66597_DIR ; 
 int R8A66597_SHTNAK ; 
 int /*<<< orphan*/  get_pipectr_addr (scalar_t__) ; 
 int make_devsel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_bset (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_write (struct r8a66597*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_buffer_setting(struct r8a66597 *r8a66597,
				struct r8a66597_pipe_info *info)
{
	u16 val = 0;

	if (info->pipenum == 0)
		return;

	r8a66597_bset(r8a66597, ACLRM, get_pipectr_addr(info->pipenum));
	r8a66597_bclr(r8a66597, ACLRM, get_pipectr_addr(info->pipenum));
	r8a66597_write(r8a66597, info->pipenum, PIPESEL);
	if (!info->dir_in)
		val |= R8A66597_DIR;
	if (info->type == R8A66597_BULK && info->dir_in)
		val |= R8A66597_DBLB | R8A66597_SHTNAK;
	val |= info->type | info->epnum;
	r8a66597_write(r8a66597, val, PIPECFG);

	r8a66597_write(r8a66597, (info->buf_bsize << 10) | (info->bufnum),
		       PIPEBUF);
	r8a66597_write(r8a66597, make_devsel(info->address) | info->maxpacket,
		       PIPEMAXP);
	r8a66597_write(r8a66597, info->interval, PIPEPERI);
}