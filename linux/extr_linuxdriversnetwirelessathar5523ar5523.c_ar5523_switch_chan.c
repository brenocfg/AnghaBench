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
struct ar5523 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*,int) ; 
 int ar5523_queue_init (struct ar5523*) ; 
 int ar5523_reset_tx_queues (struct ar5523*) ; 
 int ar5523_set_chan (struct ar5523*) ; 

__attribute__((used)) static int ar5523_switch_chan(struct ar5523 *ar)
{
	int error;

	error = ar5523_set_chan(ar);
	if (error) {
		ar5523_err(ar, "could not set chan, error %d\n", error);
		goto out_err;
	}

	/* reset Tx rings */
	error = ar5523_reset_tx_queues(ar);
	if (error) {
		ar5523_err(ar, "could not reset Tx queues, error %d\n",
			   error);
		goto out_err;
	}
	/* set Tx rings WME properties */
	error = ar5523_queue_init(ar);
	if (error)
		ar5523_err(ar, "could not init wme, error %d\n", error);

out_err:
	return error;
}