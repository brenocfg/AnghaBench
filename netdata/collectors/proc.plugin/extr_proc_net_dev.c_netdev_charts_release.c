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
struct netdev {int /*<<< orphan*/ * rd_tcompressed; int /*<<< orphan*/ * rd_tcarrier; int /*<<< orphan*/ * rd_tcollisions; int /*<<< orphan*/ * rd_tfifo; int /*<<< orphan*/ * rd_tdrops; int /*<<< orphan*/ * rd_terrors; int /*<<< orphan*/ * rd_tpackets; int /*<<< orphan*/ * rd_tbytes; int /*<<< orphan*/ * rd_rmulticast; int /*<<< orphan*/ * rd_rcompressed; int /*<<< orphan*/ * rd_rframe; int /*<<< orphan*/ * rd_rfifo; int /*<<< orphan*/ * rd_rdrops; int /*<<< orphan*/ * rd_rerrors; int /*<<< orphan*/ * rd_rpackets; int /*<<< orphan*/ * rd_rbytes; int /*<<< orphan*/ * st_packets; int /*<<< orphan*/ * st_fifo; int /*<<< orphan*/ * st_events; int /*<<< orphan*/ * st_errors; int /*<<< orphan*/ * st_drops; int /*<<< orphan*/ * st_compressed; int /*<<< orphan*/ * st_bandwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  rrdset_is_obsolete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netdev_charts_release(struct netdev *d) {
    if(d->st_bandwidth)  rrdset_is_obsolete(d->st_bandwidth);
    if(d->st_packets)    rrdset_is_obsolete(d->st_packets);
    if(d->st_errors)     rrdset_is_obsolete(d->st_errors);
    if(d->st_drops)      rrdset_is_obsolete(d->st_drops);
    if(d->st_fifo)       rrdset_is_obsolete(d->st_fifo);
    if(d->st_compressed) rrdset_is_obsolete(d->st_compressed);
    if(d->st_events)     rrdset_is_obsolete(d->st_events);

    d->st_bandwidth   = NULL;
    d->st_compressed  = NULL;
    d->st_drops       = NULL;
    d->st_errors      = NULL;
    d->st_events      = NULL;
    d->st_fifo        = NULL;
    d->st_packets     = NULL;

    d->rd_rbytes      = NULL;
    d->rd_rpackets    = NULL;
    d->rd_rerrors     = NULL;
    d->rd_rdrops      = NULL;
    d->rd_rfifo       = NULL;
    d->rd_rframe      = NULL;
    d->rd_rcompressed = NULL;
    d->rd_rmulticast  = NULL;

    d->rd_tbytes      = NULL;
    d->rd_tpackets    = NULL;
    d->rd_terrors     = NULL;
    d->rd_tdrops      = NULL;
    d->rd_tfifo       = NULL;
    d->rd_tcollisions = NULL;
    d->rd_tcarrier    = NULL;
    d->rd_tcompressed = NULL;
}