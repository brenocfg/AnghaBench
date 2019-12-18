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
typedef  int u32 ;
struct pcxhr_mgr {int async_err_other_last; int /*<<< orphan*/  async_err_pipe_xrun; int /*<<< orphan*/  async_err_stream_xrun; TYPE_1__* pci; } ;
typedef  enum pcxhr_async_err_src { ____Placeholder_pcxhr_async_err_src } pcxhr_async_err_src ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  PCXHR_ERR_AUDIO 130 
#define  PCXHR_ERR_PIPE 129 
#define  PCXHR_ERR_STREAM 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,char*,int,int) ; 

__attribute__((used)) static int pcxhr_handle_async_err(struct pcxhr_mgr *mgr, u32 err,
				  enum pcxhr_async_err_src err_src, int pipe,
				  int is_capture)
{
	static char* err_src_name[] = {
		[PCXHR_ERR_PIPE]	= "Pipe",
		[PCXHR_ERR_STREAM]	= "Stream",
		[PCXHR_ERR_AUDIO]	= "Audio"
	};

	if (err & 0xfff)
		err &= 0xfff;
	else
		err = ((err >> 12) & 0xfff);
	if (!err)
		return 0;
	dev_dbg(&mgr->pci->dev, "CMD_ASYNC : Error %s %s Pipe %d err=%x\n",
		    err_src_name[err_src],
		    is_capture ? "Record" : "Play", pipe, err);
	if (err == 0xe01)
		mgr->async_err_stream_xrun++;
	else if (err == 0xe10)
		mgr->async_err_pipe_xrun++;
	else
		mgr->async_err_other_last = (int)err;
	return 1;
}