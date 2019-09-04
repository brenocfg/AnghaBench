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
typedef  size_t uint64_t ;
struct Throttler {double max_rate; int index; int batch_size; double current_rate; size_t test_timestamp; size_t test_packet_count; TYPE_1__* buckets; } ;
struct TYPE_2__ {size_t timestamp; size_t packet_count; } ;

/* Variables and functions */
 size_t pixie_gettime () ; 
 int /*<<< orphan*/  pixie_usleep (size_t) ; 

uint64_t
throttler_next_batch(struct Throttler *throttler, uint64_t packet_count)
{
    uint64_t timestamp;
    uint64_t index;
    uint64_t old_timestamp;
    uint64_t old_packet_count;
    double current_rate;
    double max_rate = throttler->max_rate;

again:

    /* NOTE: this uses CLOCK_MONOTONIC_RAW on Linux, so the timstamp doesn't
     * move forward when the machine is suspended */
    timestamp = pixie_gettime();

    /*
     * We record that last 256 buckets, and average the rate over all of
     * them.
     */
    index = (throttler->index) & 0xFF;
    throttler->buckets[index].timestamp = timestamp;
    throttler->buckets[index].packet_count = packet_count;

    index = (++throttler->index) & 0xFF;
    old_timestamp = throttler->buckets[index].timestamp;
    old_packet_count = throttler->buckets[index].packet_count;

    /*
     * If the delay is more than 1-second, then we should reset the system
     * in order to avoid transmittting too fast.
     */
    if (timestamp - old_timestamp > 1000000) {
        //throttler_start(throttler, throttler->max_rate);
        throttler->batch_size = 1;
        goto again;
    }

    /*
     * Calculate the recent rate.
     * NOTE: this isn't the rate "since start", but only the "recent" rate.
     * That's so that if the system pauses for a while, we don't flood the
     * network trying to catch up.
     */
    current_rate = 1.0*(packet_count - old_packet_count)/((timestamp - old_timestamp)/1000000.0);


    /*
     * If we've been going too fast, then <pause> for a moment, then
     * try again.
     */
    if (current_rate > max_rate) {
        double waittime;

        /* calculate waittime, in seconds */
        waittime = (current_rate - max_rate) / throttler->max_rate;

        /* At higher rates of speed, we don't actually need to wait the full
         * interval. It's better to have a much smaller interval, so that
         * we converge back on the true rate faster */
        waittime *= 0.1;

        /* This is in case of gross failure of the system. This should never
         * actually happen, unless there is a bug. Really, I ought to make
         * this an 'assert()' instead to fail and fix the bug rather than
         * silently continueing, but I'm too lazy */
        if (waittime > 0.1)
            waittime = 0.1;

        /* Since we've exceeded the speed limit, we should reduce the
         * batch size slightly. We don't do it only by a little bit to
         * avoid over-correcting. We want to converge on the correct
         * speed gradually. Note that since this happens hundres or
         * thousands of times a second, the convergence is very fast
         * even with 0.1% adjustment */
        throttler->batch_size *= 0.999;

        /* Now we wait for a bit */
        pixie_usleep((uint64_t)(waittime * 1000000.0));

        /* There are two choices here. We could either return immediately,
         * or we can loop around again. Right now, the code loops around
         * again in order to support very slow rates, such as 0.5 packets
         * per second. Nobody would want to run a scanner that slowly of
         * course, but it's great for testing */
        //return (uint64_t)throttler->batch_size;
        goto again;
    }

    /*
     * Calculate how many packets are needed to catch up again to the current
     * rate, and return that.
     *
     * NOTE: this is almost always going to have the value of 1 (one). Only at
     * very high speeds (above 100,000 packets/second) will this value get
     * larger.
     */
    throttler->batch_size *= 1.005;
    if (throttler->batch_size > 10000)
        throttler->batch_size = 10000;
    throttler->current_rate = current_rate;

    throttler->test_timestamp = timestamp;
    throttler->test_packet_count = packet_count;
    return (uint64_t)throttler->batch_size;
}