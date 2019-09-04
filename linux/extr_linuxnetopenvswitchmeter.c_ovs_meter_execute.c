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
typedef  int u32 ;
struct sw_flow_key {int dummy; } ;
struct sk_buff {int len; } ;
struct TYPE_4__ {int n_packets; int n_bytes; } ;
struct dp_meter_band {long long burst_size; long long rate; int bucket; scalar_t__ type; TYPE_2__ stats; } ;
struct TYPE_3__ {int n_packets; int n_bytes; } ;
struct dp_meter {long long used; int max_delta_t; int n_bands; int /*<<< orphan*/  lock; struct dp_meter_band* bands; scalar_t__ kbps; TYPE_1__ stats; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 scalar_t__ OVS_METER_BAND_TYPE_DROP ; 
 long long div_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 struct dp_meter* lookup_meter (struct datapath*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool ovs_meter_execute(struct datapath *dp, struct sk_buff *skb,
		       struct sw_flow_key *key, u32 meter_id)
{
	struct dp_meter *meter;
	struct dp_meter_band *band;
	long long int now_ms = div_u64(ktime_get_ns(), 1000 * 1000);
	long long int long_delta_ms;
	u32 delta_ms;
	u32 cost;
	int i, band_exceeded_max = -1;
	u32 band_exceeded_rate = 0;

	meter = lookup_meter(dp, meter_id);
	/* Do not drop the packet when there is no meter. */
	if (!meter)
		return false;

	/* Lock the meter while using it. */
	spin_lock(&meter->lock);

	long_delta_ms = (now_ms - meter->used); /* ms */

	/* Make sure delta_ms will not be too large, so that bucket will not
	 * wrap around below.
	 */
	delta_ms = (long_delta_ms > (long long int)meter->max_delta_t)
		   ? meter->max_delta_t : (u32)long_delta_ms;

	/* Update meter statistics.
	 */
	meter->used = now_ms;
	meter->stats.n_packets += 1;
	meter->stats.n_bytes += skb->len;

	/* Bucket rate is either in kilobits per second, or in packets per
	 * second.  We maintain the bucket in the units of either bits or
	 * 1/1000th of a packet, correspondingly.
	 * Then, when rate is multiplied with milliseconds, we get the
	 * bucket units:
	 * msec * kbps = bits, and
	 * msec * packets/sec = 1/1000 packets.
	 *
	 * 'cost' is the number of bucket units in this packet.
	 */
	cost = (meter->kbps) ? skb->len * 8 : 1000;

	/* Update all bands and find the one hit with the highest rate. */
	for (i = 0; i < meter->n_bands; ++i) {
		long long int max_bucket_size;

		band = &meter->bands[i];
		max_bucket_size = (band->burst_size + band->rate) * 1000LL;

		band->bucket += delta_ms * band->rate;
		if (band->bucket > max_bucket_size)
			band->bucket = max_bucket_size;

		if (band->bucket >= cost) {
			band->bucket -= cost;
		} else if (band->rate > band_exceeded_rate) {
			band_exceeded_rate = band->rate;
			band_exceeded_max = i;
		}
	}

	if (band_exceeded_max >= 0) {
		/* Update band statistics. */
		band = &meter->bands[band_exceeded_max];
		band->stats.n_packets += 1;
		band->stats.n_bytes += skb->len;

		/* Drop band triggered, let the caller drop the 'skb'.  */
		if (band->type == OVS_METER_BAND_TYPE_DROP) {
			spin_unlock(&meter->lock);
			return true;
		}
	}

	spin_unlock(&meter->lock);
	return false;
}