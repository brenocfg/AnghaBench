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
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 char* name_from_ip_proto (unsigned int) ; 
 char* status_string (int) ; 

__attribute__((used)) static void
text_out_status(struct Output *out, FILE *fp, time_t timestamp,
    int status, unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    UNUSEDPARM(ttl);
    UNUSEDPARM(reason);
    UNUSEDPARM(out);


    fprintf(fp, "%s %s %u %u.%u.%u.%u %u\n",
        status_string(status),
        name_from_ip_proto(ip_proto),
        port,
        (ip>>24)&0xFF,
        (ip>>16)&0xFF,
        (ip>> 8)&0xFF,
        (ip>> 0)&0xFF,
        (unsigned)timestamp
        );
}