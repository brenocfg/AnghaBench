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
struct snd_usb_substream {int /*<<< orphan*/  data_endpoint; int /*<<< orphan*/  sync_endpoint; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUBSTREAM_FLAG_DATA_EP_STARTED ; 
 int /*<<< orphan*/  SUBSTREAM_FLAG_SYNC_EP_STARTED ; 
 int /*<<< orphan*/  snd_usb_endpoint_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_endpoint_sync_pending_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_endpoints(struct snd_usb_substream *subs, bool wait)
{
	if (test_and_clear_bit(SUBSTREAM_FLAG_SYNC_EP_STARTED, &subs->flags))
		snd_usb_endpoint_stop(subs->sync_endpoint);

	if (test_and_clear_bit(SUBSTREAM_FLAG_DATA_EP_STARTED, &subs->flags))
		snd_usb_endpoint_stop(subs->data_endpoint);

	if (wait) {
		snd_usb_endpoint_sync_pending_stop(subs->sync_endpoint);
		snd_usb_endpoint_sync_pending_stop(subs->data_endpoint);
	}
}