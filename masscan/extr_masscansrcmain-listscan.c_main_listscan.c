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
typedef  int uint64_t ;
struct TYPE_4__ {int index; int count; } ;
struct TYPE_3__ {unsigned int of; int one; } ;
struct Masscan {int seed; int retries; int max_rate; scalar_t__ is_infinite; scalar_t__ is_test_csv; int /*<<< orphan*/  ports; int /*<<< orphan*/  targets; TYPE_2__ resume; TYPE_1__ shard; int /*<<< orphan*/  blackrock_rounds; } ;
struct BlackRock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  blackrock_init (struct BlackRock*,int,int,int /*<<< orphan*/ ) ; 
 int blackrock_shuffle (struct BlackRock*,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  rangelist_add_range (int /*<<< orphan*/ *,int,int) ; 
 int rangelist_count (int /*<<< orphan*/ *) ; 
 unsigned int rangelist_pick (int /*<<< orphan*/ *,int) ; 

void
main_listscan(struct Masscan *masscan)
{
    uint64_t count_ips;
    uint64_t count_ports;
    uint64_t i;
    uint64_t range;
    uint64_t start;
    uint64_t end;
    struct BlackRock blackrock;
    unsigned increment = masscan->shard.of;
    uint64_t seed = masscan->seed;

    count_ports = rangelist_count(&masscan->ports);
    if (count_ports == 0)
        rangelist_add_range(&masscan->ports, 80, 80);
    count_ports = rangelist_count(&masscan->ports);

    count_ips = rangelist_count(&masscan->targets);
    if (count_ips == 0) {
        LOG(0, "FAIL: target IP address list empty\n");
        LOG(0, " [hint] try something like \"--range 10.0.0.0/8\"\n");
        LOG(0, " [hint] try something like \"--range 192.168.0.100-192.168.0.200\"\n");
        return;
    }

    range = count_ips * count_ports;

infinite:
    blackrock_init(&blackrock, range, seed, masscan->blackrock_rounds);

    start = masscan->resume.index + (masscan->shard.one-1);
    end = range;
    if (masscan->resume.count && end > start + masscan->resume.count)
        end = start + masscan->resume.count;
    end += (uint64_t)(masscan->retries * masscan->max_rate);

//printf("start=%llu, end=%llu\n", start, end);
    for (i=start; i<end; ) {
        uint64_t xXx;
        unsigned ip;
        unsigned port;

        xXx = blackrock_shuffle(&blackrock,  i);

        ip = rangelist_pick(&masscan->targets, xXx % count_ips);
        port = rangelist_pick(&masscan->ports, xXx / count_ips);

        if (count_ports == 1) {
            if (masscan->is_test_csv) {
                /* [KLUDGE] [TEST]
                 * For testing randomness output, prints last two bytes of
                 * IP address as CSV format for import into spreadsheet
                 */
                printf("%u,%u\n",
                       (ip>>8)&0xFF, (ip>>0)&0xFF
                       );
            } else {
                printf("%u.%u.%u.%u\n",
                       (ip>>24)&0xFF, (ip>>16)&0xFF, (ip>>8)&0xFF, (ip>>0)&0xFF
                       );
            }
        } else
            printf("%u.%u.%u.%u:%u\n",
                   (ip>>24)&0xFF, (ip>>16)&0xFF, (ip>>8)&0xFF, (ip>>0)&0xFF,
                   port
                   );

        i += increment; /* <------ increment by 1 normally, more with shards/nics */
    }

    if (masscan->is_infinite) {
        seed++;
        goto infinite;
    }
}