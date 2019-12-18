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
struct Output {unsigned char when_scan_started; } ;
struct MasscanRecord {unsigned char timestamp; unsigned char ip; unsigned char port; unsigned char reason; unsigned char ttl; int ip_proto; int /*<<< orphan*/  mac; } ;
typedef  enum PortStatus { ____Placeholder_PortStatus } PortStatus ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_report_status (struct Output*,unsigned char,int,unsigned char,int,int,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_status(struct Output *out,
        enum PortStatus status, /* open/closed */
        const unsigned char *buf, size_t buf_length)
{
    struct MasscanRecord record;

    if (buf_length < 12)
        return;

    /* parse record */
    record.timestamp = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];
    record.ip        = buf[4]<<24 | buf[5]<<16 | buf[6]<<8 | buf[7];
    record.port      = buf[8]<<8 | buf[9];
    record.reason    = buf[10];
    record.ttl       = buf[11];

    /* if ARP, then there will be a MAC address */
    if (record.ip == 0 && buf_length >= 12+6)
        memcpy(record.mac, buf+12, 6);
    else
        memset(record.mac, 0, 6);

    if (out->when_scan_started == 0)
        out->when_scan_started = record.timestamp;

    switch (record.port) {
    case 53:
    case 123:
    case 137:
    case 161: 
        record.ip_proto = 17;
        break;
    case 36422:
    case 36412:
    case 2905:
        record.ip_proto = 132;
        break;
    default:
        record.ip_proto = 6;
        break;
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