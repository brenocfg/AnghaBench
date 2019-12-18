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
struct scm_timestamping {int /*<<< orphan*/ * ts; } ;

/* Variables and functions */
#define  SCM_TSTAMP_ACK 130 
#define  SCM_TSTAMP_SCHED 129 
#define  SCM_TSTAMP_SND 128 
 int /*<<< orphan*/  __print_timestamp (char const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cfg_delay_ack ; 
 int /*<<< orphan*/  cfg_delay_snd ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  validate_key (int,int) ; 
 int /*<<< orphan*/  validate_timestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_timestamp(struct scm_timestamping *tss, int tstype,
			    int tskey, int payload_len)
{
	const char *tsname;

	validate_key(tskey, tstype);

	switch (tstype) {
	case SCM_TSTAMP_SCHED:
		tsname = "  ENQ";
		validate_timestamp(&tss->ts[0], 0);
		break;
	case SCM_TSTAMP_SND:
		tsname = "  SND";
		validate_timestamp(&tss->ts[0], cfg_delay_snd);
		break;
	case SCM_TSTAMP_ACK:
		tsname = "  ACK";
		validate_timestamp(&tss->ts[0], cfg_delay_ack);
		break;
	default:
		error(1, 0, "unknown timestamp type: %u",
		tstype);
	}
	__print_timestamp(tsname, &tss->ts[0], tskey, payload_len);
}