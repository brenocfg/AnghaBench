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
typedef  scalar_t__ time_t ;
struct Output {int is_first_record_seen; } ;
typedef  int /*<<< orphan*/  reason_buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* name_from_ip_proto (unsigned int) ; 
 char* reason_string (unsigned int,char*,int) ; 
 char* status_string (int) ; 

__attribute__((used)) static void
json_out_status(struct Output *out, FILE *fp, time_t timestamp, int status,
               unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    char reason_buffer[128];
    UNUSEDPARM(out);
    //UNUSEDPARM(timestamp);

    /* Trailing comma breaks some JSON parsers. We don't know precisely when
     * we'll end, but we do know when we begin, so instead of appending
     * a command to the record, we prepend it -- but not before first record */
    if (out->is_first_record_seen)
        fprintf(fp, ",\n");
    else
        out->is_first_record_seen = 1;
    
    fprintf(fp, "{ ");
    fprintf(fp, "  \"ip\": \"%u.%u.%u.%u\", ",
            (ip>>24)&0xFF, (ip>>16)&0xFF, (ip>> 8)&0xFF, (ip>> 0)&0xFF);
    fprintf(fp, "  \"timestamp\": \"%d\", \"ports\": [ {\"port\": %u, \"proto\": \"%s\", \"status\": \"%s\","
                " \"reason\": \"%s\", \"ttl\": %u} ] ",
                (int) timestamp,
                port,
                name_from_ip_proto(ip_proto),
                status_string(status),
                reason_string(reason, reason_buffer, sizeof(reason_buffer)),
                ttl
            );
    fprintf(fp, "}\n");


}