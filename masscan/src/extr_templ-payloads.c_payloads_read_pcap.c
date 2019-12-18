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
struct RangeList {int count; int max; struct Range* list; int /*<<< orphan*/  member_0; } ;
struct Range {int /*<<< orphan*/  begin; int /*<<< orphan*/  end; int /*<<< orphan*/  member_0; } ;
struct PreprocessedInfo {int found; int /*<<< orphan*/  transport_length; int /*<<< orphan*/  transport_offset; int /*<<< orphan*/  ip_protocol; int /*<<< orphan*/  app_length; int /*<<< orphan*/  app_offset; int /*<<< orphan*/  port_dst; } ;
struct PcapFile {int dummy; } ;
struct PayloadsUDP {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  FOUND_DNS 130 
#define  FOUND_OPROTO 129 
#define  FOUND_UDP 128 
 int /*<<< orphan*/  LOG (int,char*,char const*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 unsigned int payloads_datagram_add (struct PayloadsUDP*,unsigned char*,int /*<<< orphan*/ ,struct RangeList*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcapfile_close (struct PcapFile*) ; 
 struct PcapFile* pcapfile_openread (char const*) ; 
 unsigned int pcapfile_readframe (struct PcapFile*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned char*,unsigned int) ; 
 unsigned int preprocess_frame (unsigned char*,unsigned int,int,struct PreprocessedInfo*) ; 
 int /*<<< orphan*/  stderr ; 

void
payloads_read_pcap(const char *filename,
                   struct PayloadsUDP *payloads,
                   struct PayloadsUDP *oproto_payloads)
{
    struct PcapFile *pcap;
    unsigned count = 0;

    LOG(2, "payloads:'%s': opening packet capture\n", filename);

    /* open packet-capture */
    pcap = pcapfile_openread(filename);
    if (pcap == NULL) {
        fprintf(stderr, "payloads: can't read from file '%s'\n", filename);
        return;
    }

    /* for all packets in the capture file
     *  - read in packet
     *  - parse packet
     *  - save payload
     */
    for (;;) {
        unsigned x;
        unsigned captured_length;
        unsigned char buf[65536];
        struct PreprocessedInfo parsed;
        struct RangeList ports[1] = {{0}};
        struct Range range[1] = {{0}};

        /*
         * Read the next packet from the capture file
         */
        {
            unsigned time_secs;
            unsigned time_usecs;
            unsigned original_length;

            x = pcapfile_readframe(pcap,
                    &time_secs, &time_usecs,
                    &original_length, &captured_length,
                    buf, (unsigned)sizeof(buf));
        }
        if (!x)
            break;

        /*
         * Parse the packet up to its headers
         */
        x = preprocess_frame(buf, captured_length, 1, &parsed);
        if (!x)
            continue; /* corrupt packet */

        /*
         * Make sure it has UDP
         */
        switch (parsed.found) {
        case FOUND_DNS:
        case FOUND_UDP:
                /*
                 * Kludge: mark the port in the format the API wants
                 */
                ports->list = range;
                ports->count = 1;
                ports->max = 1;
                range->begin = parsed.port_dst;
                range->end = range->begin;
                
                /*
                 * Now we've completely parsed the record, so add it to our
                 * list of payloads
                 */
                count += payloads_datagram_add(   payloads,
                                          buf + parsed.app_offset,
                                          parsed.app_length,
                                          ports,
                                          0x10000,
                                          0);
            break;
        case FOUND_OPROTO:
                /*
                 * Kludge: mark the port in the format the API wants
                 */
                ports->list = range;
                ports->count = 1;
                ports->max = 1;
                range->begin = parsed.ip_protocol;
                range->end = range->begin;
                
                /*
                 * Now we've completely parsed the record, so add it to our
                 * list of payloads
                 */
                count += payloads_datagram_add(oproto_payloads,
                                          buf + parsed.transport_offset,
                                          parsed.transport_length,
                                          ports,
                                          0x10000,
                                          0);
            break;
        default:
            continue;
        }

    }

    LOG(2, "payloads:'%s': imported %u unique payloads\n", filename, count);
    LOG(2, "payloads:'%s': closed packet capture\n", filename);
    pcapfile_close(pcap);
}