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
struct mxs_ocotp {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 unsigned int BM_OCOTP_CTRL_BUSY ; 
 unsigned int BM_OCOTP_CTRL_ERROR ; 
 int EBUSY ; 
 int EIO ; 
 int OCOTP_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxs_ocotp_wait(struct mxs_ocotp *otp)
{
	int timeout = OCOTP_TIMEOUT;
	unsigned int status = 0;

	while (timeout--) {
		status = readl(otp->base);

		if (!(status & (BM_OCOTP_CTRL_BUSY | BM_OCOTP_CTRL_ERROR)))
			break;

		cpu_relax();
	}

	if (status & BM_OCOTP_CTRL_BUSY)
		return -EBUSY;
	else if (status & BM_OCOTP_CTRL_ERROR)
		return -EIO;

	return 0;
}