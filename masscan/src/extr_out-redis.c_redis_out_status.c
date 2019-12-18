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
typedef  int /*<<< orphan*/  values ;
typedef  scalar_t__ time_t ;
struct TYPE_2__ {int /*<<< orphan*/  outstanding; } ;
struct Output {TYPE_1__ redis; } ;
typedef  scalar_t__ ptrdiff_t ;
typedef  int /*<<< orphan*/  port_string ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  ip_string ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clean_response_queue (struct Output*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* name_from_ip_proto (unsigned int) ; 
 size_t send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int sprintf_s (char*,int,char*,int,...) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
redis_out_status(struct Output *out, FILE *fp, time_t timestamp,
    int status, unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    ptrdiff_t fd = (ptrdiff_t)fp;
    char line[1024];
    int line_length;
    char ip_string[16];
    char port_string[10];
    int ip_string_length;
    int port_string_length;
    size_t count;
    char values[64];
    int values_length;

    ip_string_length = sprintf_s(ip_string, sizeof(ip_string), "%u.%u.%u.%u",
        (unsigned char)(ip>>24),
        (unsigned char)(ip>>16),
        (unsigned char)(ip>> 8),
        (unsigned char)(ip>> 0));
    port_string_length = sprintf_s(port_string, sizeof(port_string), "%u/%s", port, name_from_ip_proto(ip_proto));

/**3
$3
SET
$5
mykey
$7
myvalue
*/

    /*
     * KEY: "host"
     * VALUE: ip
     */
    sprintf_s(line, sizeof(line),
            "*3\r\n"
            "$4\r\nSADD\r\n"
            "$%d\r\n%s\r\n"
            "$%d\r\n%s\r\n"
            ,
            4, "host",
            ip_string_length, ip_string
            );

    count = send((SOCKET)fd, line, (int)strlen(line), 0);
    if (count != strlen(line)) {
        LOG(0, "redis: error sending data\n");
        exit(1);
    }
    out->redis.outstanding++;

    /*
     * KEY: ip
     * VALUE: port
     */
    sprintf_s(line, sizeof(line),
            "*3\r\n"
            "$4\r\nSADD\r\n"
            "$%d\r\n%s\r\n"
            "$%d\r\n%s\r\n"
            ,
            ip_string_length, ip_string,
            port_string_length, port_string);

    count = send((SOCKET)fd, line, (int)strlen(line), 0);
    if (count != strlen(line)) {
        LOG(0, "redis: error sending data\n");
        exit(1);
    }
    out->redis.outstanding++;


    /*
     * KEY: ip:port
     * VALUE: timestamp:status:reason:ttl
     */
    values_length = sprintf_s(values, sizeof(values), "%u:%u:%u:%u",
        (unsigned)timestamp, status, reason, ttl);
    line_length = sprintf_s(line, sizeof(line),
            "*3\r\n"
            "$4\r\nSADD\r\n"
            "$%d\r\n%s:%s\r\n"
            "$%d\r\n%s\r\n"
            ,
            ip_string_length + 1 + port_string_length,
            ip_string, port_string,
            values_length, values
            );

    count = send((SOCKET)fd, line, (int)line_length, 0);
    if (count != (size_t)line_length) {
        LOG(0, "redis: error sending data\n");
        exit(1);
    }
    out->redis.outstanding++;

    clean_response_queue(out, (SOCKET)fd);

}