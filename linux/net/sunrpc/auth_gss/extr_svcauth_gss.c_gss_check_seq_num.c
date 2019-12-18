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
struct gss_svc_seq_data {int sd_max; int /*<<< orphan*/  sd_lock; int /*<<< orphan*/  sd_win; } ;
struct rsc {struct gss_svc_seq_data seqdata; } ;

/* Variables and functions */
 int GSS_SEQ_WIN ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ __test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gss_check_seq_num(struct rsc *rsci, int seq_num)
{
	struct gss_svc_seq_data *sd = &rsci->seqdata;

	spin_lock(&sd->sd_lock);
	if (seq_num > sd->sd_max) {
		if (seq_num >= sd->sd_max + GSS_SEQ_WIN) {
			memset(sd->sd_win,0,sizeof(sd->sd_win));
			sd->sd_max = seq_num;
		} else while (sd->sd_max < seq_num) {
			sd->sd_max++;
			__clear_bit(sd->sd_max % GSS_SEQ_WIN, sd->sd_win);
		}
		__set_bit(seq_num % GSS_SEQ_WIN, sd->sd_win);
		goto ok;
	} else if (seq_num <= sd->sd_max - GSS_SEQ_WIN) {
		goto drop;
	}
	/* sd_max - GSS_SEQ_WIN < seq_num <= sd_max */
	if (__test_and_set_bit(seq_num % GSS_SEQ_WIN, sd->sd_win))
		goto drop;
ok:
	spin_unlock(&sd->sd_lock);
	return 1;
drop:
	spin_unlock(&sd->sd_lock);
	return 0;
}