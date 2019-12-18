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
struct MasscanRecord {unsigned char timestamp; unsigned char ip; unsigned char ip_proto; unsigned char port; unsigned char app_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_report_banner (struct Output*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 

__attribute__((used)) static void
parse_banner4(struct Output *out, unsigned char *buf, size_t buf_length)
{
    struct MasscanRecord record;

    if (buf_length < 13)
        return;

    /*
     * Parse the parts that are common to most records
     */
    record.timestamp = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];
    record.ip        = buf[4]<<24 | buf[5]<<16 | buf[6]<<8 | buf[7];
    record.ip_proto  = buf[8];
    record.port      = buf[9]<<8 | buf[10];
    record.app_proto = buf[11]<<8 | buf[12];

    if (out->when_scan_started == 0)
        out->when_scan_started = record.timestamp;

    /*
     * Now print the output
     */
    output_report_banner(
                out,
                record.timestamp,
                record.ip,
                record.ip_proto,    /* TCP=6, UDP=17 */
                record.port,
                record.app_proto,   /* HTTP, SSL, SNMP, etc. */
                0, /* ttl */
                buf+13, (unsigned)buf_length-13
                );
}