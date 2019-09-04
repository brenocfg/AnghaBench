#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  void* u16 ;
struct brcms_c_info {void* tx_duty_cycle_cck; void* tx_duty_cycle_ofdm; TYPE_2__* hw; TYPE_1__* pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_3__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_TX_IDLE_BUSY_RATIO_X_16_CCK ; 
 int /*<<< orphan*/  M_TX_IDLE_BUSY_RATIO_X_16_OFDM ; 
 int /*<<< orphan*/  brcms_b_write_shm (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
brcms_c_duty_cycle_set(struct brcms_c_info *wlc, int duty_cycle, bool isOFDM,
		   bool writeToShm)
{
	int idle_busy_ratio_x_16 = 0;
	uint offset =
	    isOFDM ? M_TX_IDLE_BUSY_RATIO_X_16_OFDM :
	    M_TX_IDLE_BUSY_RATIO_X_16_CCK;
	if (duty_cycle > 100 || duty_cycle < 0) {
		brcms_err(wlc->hw->d11core,
			  "wl%d:  duty cycle value off limit\n",
			  wlc->pub->unit);
		return -EINVAL;
	}
	if (duty_cycle)
		idle_busy_ratio_x_16 = (100 - duty_cycle) * 16 / duty_cycle;
	/* Only write to shared memory  when wl is up */
	if (writeToShm)
		brcms_b_write_shm(wlc->hw, offset, (u16) idle_busy_ratio_x_16);

	if (isOFDM)
		wlc->tx_duty_cycle_ofdm = (u16) duty_cycle;
	else
		wlc->tx_duty_cycle_cck = (u16) duty_cycle;

	return 0;
}