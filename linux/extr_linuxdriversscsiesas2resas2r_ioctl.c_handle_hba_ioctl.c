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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_buffered_ioctl {scalar_t__ offset; int /*<<< orphan*/ * done_context; int /*<<< orphan*/  done_callback; int /*<<< orphan*/ * context; int /*<<< orphan*/  callback; scalar_t__ length; struct atto_ioctl* ioctl; struct esas2r_adapter* a; } ;
struct esas2r_adapter {int dummy; } ;
struct atto_ioctl {scalar_t__ data_length; } ;
typedef  int /*<<< orphan*/  bi ;

/* Variables and functions */
 int /*<<< orphan*/  handle_buffered_ioctl (struct esas2r_buffered_ioctl*) ; 
 int /*<<< orphan*/  hba_ioctl_callback ; 
 int /*<<< orphan*/  hba_ioctl_done_callback ; 
 int /*<<< orphan*/  memset (struct esas2r_buffered_ioctl*,int /*<<< orphan*/ ,int) ; 

u8 handle_hba_ioctl(struct esas2r_adapter *a,
		    struct atto_ioctl *ioctl_hba)
{
	struct esas2r_buffered_ioctl bi;

	memset(&bi, 0, sizeof(bi));

	bi.a = a;
	bi.ioctl = ioctl_hba;
	bi.length = sizeof(struct atto_ioctl) + ioctl_hba->data_length;
	bi.callback = hba_ioctl_callback;
	bi.context = NULL;
	bi.done_callback = hba_ioctl_done_callback;
	bi.done_context = NULL;
	bi.offset = 0;

	return handle_buffered_ioctl(&bi);
}