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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  format; } ;
struct srp_event_struct {void (* done ) (struct srp_event_struct*) ;TYPE_1__ crq; int /*<<< orphan*/ * sync_srp; int /*<<< orphan*/ * cmnd_done; int /*<<< orphan*/ * cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static void init_event_struct(struct srp_event_struct *evt_struct,
			      void (*done) (struct srp_event_struct *),
			      u8 format,
			      int timeout)
{
	evt_struct->cmnd = NULL;
	evt_struct->cmnd_done = NULL;
	evt_struct->sync_srp = NULL;
	evt_struct->crq.format = format;
	evt_struct->crq.timeout = cpu_to_be16(timeout);
	evt_struct->done = done;
}