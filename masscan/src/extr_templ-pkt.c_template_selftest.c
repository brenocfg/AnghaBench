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
typedef  int /*<<< orphan*/  tmplset ;
struct TemplateSet {TYPE_1__* pkts; } ;
struct TYPE_2__ {size_t proto; } ;

/* Variables and functions */
 size_t Proto_ICMP_ping ; 
 size_t Proto_TCP ; 
 size_t Proto_UDP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct TemplateSet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  template_packet_init (struct TemplateSet*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
template_selftest(void)
{
    struct TemplateSet tmplset[1];
    int failures = 0;

    memset(tmplset, 0, sizeof(tmplset[0]));
    template_packet_init(
            tmplset,
            (const unsigned char*)"\x00\x11\x22\x33\x44\x55",
            (const unsigned char*)"\x66\x55\x44\x33\x22\x11",
            0,  /* UDP payloads = empty */
            0,  /* Oproto payloads = empty */
            1,  /* Ethernet */
            0   /* no entropy */
            );
    failures += tmplset->pkts[Proto_TCP].proto  != Proto_TCP;
    failures += tmplset->pkts[Proto_UDP].proto  != Proto_UDP;
    //failures += tmplset->pkts[Proto_SCTP].proto != Proto_SCTP;
    failures += tmplset->pkts[Proto_ICMP_ping].proto != Proto_ICMP_ping;
    //failures += tmplset->pkts[Proto_ICMP_timestamp].proto != Proto_ICMP_timestamp;
    //failures += tmplset->pkts[Proto_ARP].proto  != Proto_ARP;

    if (failures)
        fprintf(stderr, "template: failed\n");
    return failures;
}