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

/* Variables and functions */
 scalar_t__ cfg_audit ; 
 unsigned long cfg_payload_len ; 
 scalar_t__ cfg_tcp ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long total_num_msgs ; 
 unsigned long total_num_sends ; 

__attribute__((used)) static void print_report(unsigned long num_msgs, unsigned long num_sends)
{
	fprintf(stderr,
		"%s tx: %6lu MB/s %8lu calls/s %6lu msg/s\n",
		cfg_tcp ? "tcp" : "udp",
		(num_msgs * cfg_payload_len) >> 20,
		num_sends, num_msgs);

	if (cfg_audit) {
		total_num_msgs += num_msgs;
		total_num_sends += num_sends;
	}
}