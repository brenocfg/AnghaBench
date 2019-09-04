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
struct iss_ipipe_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  state; } ;
struct iss_device {struct iss_ipipe_device ipipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISS_PIPELINE_STREAM_STOPPED ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int ipipe_init_entities (struct iss_ipipe_device*) ; 

int omap4iss_ipipe_init(struct iss_device *iss)
{
	struct iss_ipipe_device *ipipe = &iss->ipipe;

	ipipe->state = ISS_PIPELINE_STREAM_STOPPED;
	init_waitqueue_head(&ipipe->wait);

	return ipipe_init_entities(ipipe);
}