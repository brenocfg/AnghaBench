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
typedef  int /*<<< orphan*/  uint64_t ;
struct thread_stats {int dummy; } ;
struct stats {int dummy; } ;
struct slab_stats {int dummy; } ;
struct settings {int dummy; } ;
typedef  int /*<<< orphan*/  item_hdr ;
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  conn ;
typedef  int /*<<< orphan*/  LIBEVENT_THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  display (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char **argv) {

    display("Slab Stats", sizeof(struct slab_stats));
    display("Thread stats",
            sizeof(struct thread_stats)
            - (200 * sizeof(struct slab_stats)));
    display("Global stats", sizeof(struct stats));
    display("Settings", sizeof(struct settings));
    display("Item (no cas)", sizeof(item));
    display("Item (cas)", sizeof(item) + sizeof(uint64_t));
#ifdef EXTSTORE
    display("extstore header", sizeof(item_hdr));
#endif
    display("Libevent thread",
            sizeof(LIBEVENT_THREAD) - sizeof(struct thread_stats));
    display("Connection", sizeof(conn));

    printf("----------------------------------------\n");

    display("libevent thread cumulative", sizeof(LIBEVENT_THREAD));
    display("Thread stats cumulative\t", sizeof(struct thread_stats));

    return 0;
}