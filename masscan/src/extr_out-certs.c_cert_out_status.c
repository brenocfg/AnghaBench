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
typedef  unsigned int time_t ;
struct Output {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned int) ; 

__attribute__((used)) static void
cert_out_status(struct Output *out, FILE *fp, time_t timestamp, int status,
                unsigned ip, unsigned ip_proto, unsigned port, unsigned reason, unsigned ttl)
{
    /* certificates only come with banner info, so there is no port info
     * to report */
    UNUSEDPARM(out);
    UNUSEDPARM(fp);
    UNUSEDPARM(timestamp);
    UNUSEDPARM(status);
    UNUSEDPARM(ip);
    UNUSEDPARM(ip_proto);
    UNUSEDPARM(port);
    UNUSEDPARM(reason);
    UNUSEDPARM(ttl);
}