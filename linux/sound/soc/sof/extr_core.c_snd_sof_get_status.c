#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sof_ipc_panic_info {int filename; int linenum; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int SOF_IPC_PANIC_CODE_MASK ; 
 int SOF_IPC_PANIC_MAGIC ; 
 int SOF_IPC_PANIC_MAGIC_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_1__* panic_msg ; 
 int /*<<< orphan*/  sof_oops (struct snd_sof_dev*,void*) ; 
 int /*<<< orphan*/  sof_stack (struct snd_sof_dev*,void*,void*,size_t) ; 

void snd_sof_get_status(struct snd_sof_dev *sdev, u32 panic_code,
			u32 tracep_code, void *oops,
			struct sof_ipc_panic_info *panic_info,
			void *stack, size_t stack_words)
{
	u32 code;
	int i;

	/* is firmware dead ? */
	if ((panic_code & SOF_IPC_PANIC_MAGIC_MASK) != SOF_IPC_PANIC_MAGIC) {
		dev_err(sdev->dev, "error: unexpected fault 0x%8.8x trace 0x%8.8x\n",
			panic_code, tracep_code);
		return; /* no fault ? */
	}

	code = panic_code & (SOF_IPC_PANIC_MAGIC_MASK | SOF_IPC_PANIC_CODE_MASK);

	for (i = 0; i < ARRAY_SIZE(panic_msg); i++) {
		if (panic_msg[i].id == code) {
			dev_err(sdev->dev, "error: %s\n", panic_msg[i].msg);
			dev_err(sdev->dev, "error: trace point %8.8x\n",
				tracep_code);
			goto out;
		}
	}

	/* unknown error */
	dev_err(sdev->dev, "error: unknown reason %8.8x\n", panic_code);
	dev_err(sdev->dev, "error: trace point %8.8x\n", tracep_code);

out:
	dev_err(sdev->dev, "error: panic at %s:%d\n",
		panic_info->filename, panic_info->linenum);
	sof_oops(sdev, oops);
	sof_stack(sdev, oops, stack, stack_words);
}