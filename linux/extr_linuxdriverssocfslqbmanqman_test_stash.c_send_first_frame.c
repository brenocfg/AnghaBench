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
typedef  scalar_t__ u32 ;
struct qm_fd {int dummy; } ;
typedef  int /*<<< orphan*/  fd ;
struct TYPE_2__ {scalar_t__ processor_id; int /*<<< orphan*/  tx; scalar_t__ tx_mixer; int /*<<< orphan*/  addr; scalar_t__* frame_ptr; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HP_FIRST_WORD ; 
 int HP_NUM_WORDS ; 
 scalar_t__ do_lfsr (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct qm_fd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  qm_fd_addr_set64 (struct qm_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_fd_set_contig_big (struct qm_fd*,int) ; 
 int qman_enqueue (int /*<<< orphan*/ *,struct qm_fd*) ; 
 scalar_t__ smp_processor_id () ; 
 TYPE_1__* special_handler ; 

__attribute__((used)) static int send_first_frame(void *ignore)
{
	u32 *p = special_handler->frame_ptr;
	u32 lfsr = HP_FIRST_WORD;
	int loop, err;
	struct qm_fd fd;

	if (special_handler->processor_id != smp_processor_id()) {
		err = -EIO;
		goto failed;
	}
	memset(&fd, 0, sizeof(fd));
	qm_fd_addr_set64(&fd, special_handler->addr);
	qm_fd_set_contig_big(&fd, HP_NUM_WORDS * 4);
	for (loop = 0; loop < HP_NUM_WORDS; loop++, p++) {
		if (*p != lfsr) {
			err = -EIO;
			pr_crit("corrupt frame data");
			goto failed;
		}
		*p ^= special_handler->tx_mixer;
		lfsr = do_lfsr(lfsr);
	}
	pr_info("Sending first frame\n");
	err = qman_enqueue(&special_handler->tx, &fd);
	if (err) {
		pr_crit("qman_enqueue() failed");
		goto failed;
	}

	return 0;
failed:
	return err;
}