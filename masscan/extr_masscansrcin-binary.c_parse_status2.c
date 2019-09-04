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
struct RangeList {scalar_t__ count; } ;
struct Output {unsigned char when_scan_started; } ;
struct MasscanRecord {unsigned char timestamp; unsigned char ip; unsigned char ip_proto; unsigned char port; unsigned char reason; unsigned char ttl; int /*<<< orphan*/  mac; } ;
typedef  enum PortStatus { ____Placeholder_PortStatus } PortStatus ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_report_status (struct Output*,unsigned char,int,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelist_is_contains (struct RangeList const*,unsigned char) ; 

__attribute__((used)) static void
parse_status2(struct Output *out,
        enum PortStatus status, /* open/closed */
        const unsigned char *buf, size_t buf_length,
        const struct RangeList *ips,
        const struct RangeList *ports)
{
    struct MasscanRecord record;

    if (buf_length < 13)
        return;

    /* parse record */
    record.timestamp = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];
    record.ip        = buf[4]<<24 | buf[5]<<16 | buf[6]<<8 | buf[7];
    record.ip_proto  = buf[8];
    record.port      = buf[9]<<8 | buf[10];
    record.reason    = buf[11];
    record.ttl       = buf[12];

    /* if ARP, then there will be a MAC address */
    if (record.ip == 0 && buf_length >= 13+6)
        memcpy(record.mac, buf+13, 6);
    else
        memset(record.mac, 0, 6);

    if (out->when_scan_started == 0)
        out->when_scan_started = record.timestamp;

    /*
     * Filter
     */
    if (ips && ips->count) {
        if (!rangelist_is_contains(ips, record.ip))
            return;
    }
    if (ports && ports->count) {
        if (!rangelist_is_contains(ports, record.port))
            return;
    }

    /*
     * Now report the result
     */
    output_report_status(out,
                    record.timestamp,
                    status,
                    record.ip,
                    record.ip_proto,
                    record.port,
                    record.reason,
                    record.ttl,
                    record.mac);

}