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
typedef  scalar_t__ uint64_t ;
struct Throttler {int dummy; } ;
struct ThreadPair {scalar_t__* total_syns; int done_transmitting; int /*<<< orphan*/  nic_index; int /*<<< orphan*/  transmit_queue; int /*<<< orphan*/  packet_buffers; scalar_t__ my_index; struct Adapter* adapter; int /*<<< orphan*/  tmplset; struct Throttler* throttler; struct Masscan* masscan; } ;
struct TemplateSet {int dummy; } ;
struct TYPE_4__ {int index; scalar_t__ count; } ;
struct TYPE_3__ {int of; int one; } ;
struct Masscan {scalar_t__ retries; scalar_t__ max_rate; int nic_count; scalar_t__ seed; scalar_t__ is_infinite; int /*<<< orphan*/  ports; int /*<<< orphan*/  targets; TYPE_2__ resume; TYPE_1__ shard; int /*<<< orphan*/  blackrock_rounds; } ;
struct BlackRock {int dummy; } ;
struct Adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*,...) ; 
 scalar_t__* MALLOC (int) ; 
 int /*<<< orphan*/  blackrock_init (struct BlackRock*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ blackrock_shuffle (struct BlackRock*,scalar_t__) ; 
 int /*<<< orphan*/  flush_packets (struct Adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  get_sources (struct Masscan const*,int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  is_rx_done ; 
 scalar_t__ is_tx_done ; 
 int /*<<< orphan*/  pixie_usleep (int) ; 
 scalar_t__ rangelist_count (int /*<<< orphan*/ *) ; 
 unsigned int rangelist_pick (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rawsock_flush (struct Adapter*) ; 
 int /*<<< orphan*/  rawsock_send_probe (struct Adapter*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int,struct TemplateSet*) ; 
 scalar_t__ syn_cookie (unsigned int,unsigned int,unsigned int,unsigned int,scalar_t__) ; 
 struct TemplateSet templ_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ throttler_next_batch (struct Throttler*,scalar_t__) ; 
 int /*<<< orphan*/  throttler_start (struct Throttler*,int) ; 

__attribute__((used)) static void
transmit_thread(void *v) /*aka. scanning_thread() */
{
    struct ThreadPair *parms = (struct ThreadPair *)v;
    uint64_t i;
    uint64_t start;
    uint64_t end;
    const struct Masscan *masscan = parms->masscan;
    uint64_t retries = masscan->retries;
    uint64_t rate = masscan->max_rate;
    unsigned r = (unsigned)retries + 1;
    uint64_t range;
    struct BlackRock blackrock;
    uint64_t count_ips = rangelist_count(&masscan->targets);
    struct Throttler *throttler = parms->throttler;
    struct TemplateSet pkt_template = templ_copy(parms->tmplset);
    struct Adapter *adapter = parms->adapter;
    uint64_t packets_sent = 0;
    unsigned increment = (masscan->shard.of-1) + masscan->nic_count;
    unsigned src_ip;
    unsigned src_ip_mask;
    unsigned src_port;
    unsigned src_port_mask;
    uint64_t seed = masscan->seed;
    uint64_t repeats = 0; /* --infinite repeats */
    uint64_t *status_syn_count;
    uint64_t entropy = masscan->seed;

    LOG(1, "THREAD: xmit: starting thread #%u\n", parms->nic_index);

    /* export a pointer to this variable outside this threads so
     * that the 'status' system can print the rate of syns we are
     * sending */
    status_syn_count = MALLOC(sizeof(uint64_t));
    *status_syn_count = 0;
    parms->total_syns = status_syn_count;


    /* Normally, we have just one source address. In special cases, though
     * we can have multiple. */
    get_sources(masscan, parms->nic_index,
                &src_ip, &src_ip_mask,
                &src_port, &src_port_mask);


    /* "THROTTLER" rate-limits how fast we transmit, set with the
     * --max-rate parameter */
    throttler_start(throttler, masscan->max_rate/masscan->nic_count);

infinite:
    
    /* Create the shuffler/randomizer. This creates the 'range' variable,
     * which is simply the number of IP addresses times the number of
     * ports */
    range = rangelist_count(&masscan->targets)
            * rangelist_count(&masscan->ports);
    blackrock_init(&blackrock, range, seed, masscan->blackrock_rounds);

    /* Calculate the 'start' and 'end' of a scan. One reason to do this is
     * to support --shard, so that multiple machines can co-operate on
     * the same scan. Another reason to do this is so that we can bleed
     * a little bit past the end when we have --retries. Yet another
     * thing to do here is deal with multiple network adapters, which
     * is essentially the same logic as shards. */
    start = masscan->resume.index + (masscan->shard.one-1) + parms->nic_index;
    end = range;
    if (masscan->resume.count && end > start + masscan->resume.count)
        end = start + masscan->resume.count;
    end += retries * rate;


    /* -----------------
     * the main loop
     * -----------------*/
    LOG(3, "THREAD: xmit: starting main loop: [%llu..%llu]\n", start, end);
    for (i=start; i<end; ) {
        uint64_t batch_size;

        /*
         * Do a batch of many packets at a time. That because per-packet
         * throttling is expensive at 10-million pps, so we reduce the
         * per-packet cost by doing batches. At slower rates, the batch
         * size will always be one. (--max-rate)
         */
        batch_size = throttler_next_batch(throttler, packets_sent);

        /*
         * Transmit packets from other thread, when doing --banners. This
         * takes priority over sending SYN packets. If there is so much
         * activity grabbing banners that we cannot transmit more SYN packets,
         * then "batch_size" will get decremented to zero, and we won't be
         * able to transmit SYN packets.
         */
        flush_packets(adapter, parms->packet_buffers, parms->transmit_queue,
                        &packets_sent, &batch_size);


        /*
         * Transmit a bunch of packets. At any rate slower than 100,000
         * packets/second, the 'batch_size' is likely to be 1
         */
        while (batch_size && i < end) {
            uint64_t xXx;
            unsigned ip_them;
            unsigned port_them;
            unsigned ip_me;
            unsigned port_me;
            uint64_t cookie;


            /*
             * RANDOMIZE THE TARGET:
             *  This is kinda a tricky bit that picks a random IP and port
             *  number in order to scan. We monotonically increment the
             *  index 'i' from [0..range]. We then shuffle (randomly transmog)
             *  that index into some other, but unique/1-to-1, number in the
             *  same range. That way we visit all targets, but in a random
             *  order. Then, once we've shuffled the index, we "pick" the
             *  IP address and port that the index refers to.
             */
            xXx = (i + (r--) * rate);
            if (rate > range)
                xXx %= range;
            else
                while (xXx >= range)
                    xXx -= range;
            xXx = blackrock_shuffle(&blackrock,  xXx);
            ip_them = rangelist_pick(&masscan->targets, xXx % count_ips);
            port_them = rangelist_pick(&masscan->ports, xXx / count_ips);

            /*
             * SYN-COOKIE LOGIC
             *  Figure out the source IP/port, and the SYN cookie
             */
            if (src_ip_mask > 1 || src_port_mask > 1) {
                uint64_t ck = syn_cookie((unsigned)(i+repeats),
                                        (unsigned)((i+repeats)>>32),
                                        (unsigned)xXx, (unsigned)(xXx>>32),
                                        entropy);
                port_me = src_port + (ck & src_port_mask);
                ip_me = src_ip + ((ck>>16) & src_ip_mask);
            } else {
                ip_me = src_ip;
                port_me = src_port;
            }
            cookie = syn_cookie(ip_them, port_them, ip_me, port_me, entropy);

            /*
             * SEND THE PROBE
             *  This is sorta the entire point of the program, but little
             *  exciting happens here. The thing to note that this may
             *  be a "raw" transmit that bypasses the kernel, meaning
             *  we can call this function millions of times a second.
             */
            rawsock_send_probe(
                    adapter,
                    ip_them, port_them,
                    ip_me, port_me,
                    (unsigned)cookie,
                    !batch_size, /* flush queue on last packet in batch */
                    &pkt_template
                    );
            batch_size--;
            packets_sent++;
            (*status_syn_count)++;

            /*
             * SEQUENTIALLY INCREMENT THROUGH THE RANGE
             *  Yea, I know this is a puny 'i++' here, but it's a core feature
             *  of the system that is linearly increments through the range,
             *  but produces from that a shuffled sequence of targets (as
             *  described above). Because we are linearly incrementing this
             *  number, we can do lots of creative stuff, like doing clever
             *  retransmits and sharding.
             */
            if (r == 0) {
                i += increment; /* <------ increment by 1 normally, more with shards/nics */
                r = (unsigned)retries + 1;
            }

        } /* end of batch */


        /* save our current location for resuming, if the user pressed
         * <ctrl-c> to exit early */
        parms->my_index = i;

        /* If the user pressed <ctrl-c>, then we need to exit. but, in case
         * the user wants to --resume the scan later, we save the current
         * state in a file */
        if (is_tx_done) {
            break;
        }
    }

    /*
     * --infinite
     *  For load testing, go around and do this again
     */
    if (masscan->is_infinite && !is_tx_done) {
        seed++;
        repeats++;
        goto infinite;
    }

    /*
     * Flush any untransmitted packets. High-speed mechanisms like Windows
     * "sendq" and Linux's "PF_RING" queue packets and transmit many together,
     * so there may be some packets that we've queueud but not yet transmitted.
     * This call makes sure they are transmitted.
     */
    rawsock_flush(adapter);

    /*
     * Wait until the receive thread realizes the scan is over
     */
    LOG(1, "THREAD: xmit done, waiting for receive thread to realize this\n");

    /*
     * We are done transmitting. However, response packets will take several
     * seconds to arrive. Therefore, sit in short loop waiting for those
     * packets to arrive. Pressing <ctrl-c> a second time will exit this
     * prematurely.
     */
    while (!is_rx_done) {
        unsigned k;
        uint64_t batch_size;

        for (k=0; k<1000; k++) {
            
            /*
             * Only send a few packets at a time, throttled according to the max
             * --max-rate set by the user
             */
            batch_size = throttler_next_batch(throttler, packets_sent);


            /* Transmit packets from the receive thread */
            flush_packets(  adapter,
                            parms->packet_buffers,
                            parms->transmit_queue,
                            &packets_sent,
                            &batch_size);

            /* Make sure they've actually been transmitted, not just queued up for
             * transmit */
            rawsock_flush(adapter);

            pixie_usleep(100);
        }
    }

    /* Thread is about to exit */
    parms->done_transmitting = 1;
    LOG(1, "THREAD: xmit: stopping thread #%u\n", parms->nic_index);
}