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
struct MasscanRecord {unsigned char timestamp; unsigned char ip; unsigned char port; unsigned char app_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_report_banner (struct Output*,unsigned char,unsigned char,int,unsigned char,unsigned char,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 

__attribute__((used)) static void
parse_banner3(struct Output *out, unsigned char *buf, size_t buf_length)
{
    struct MasscanRecord record;

    /*
     * Parse the parts that are common to most records
     */
    record.timestamp = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];
    record.ip        = buf[4]<<24 | buf[5]<<16 | buf[6]<<8 | buf[7];
    record.port      = buf[8]<<8 | buf[9];
    record.app_proto = buf[10]<<8 | buf[11];

    if (out->when_scan_started == 0)
        out->when_scan_started = record.timestamp;

    /*
     * Now print the output
     */
    output_report_banner(
                out,
                record.timestamp,
                record.ip,
                6, /* this is always TCP */
                record.port,
                record.app_proto,
                0, /* ttl */
                buf+12, (unsigned)buf_length-12
                );
}