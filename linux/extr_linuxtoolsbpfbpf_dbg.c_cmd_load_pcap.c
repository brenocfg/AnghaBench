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
 int CMD_ERR ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  try_close_pcap () ; 
 int try_load_pcap (char*) ; 

__attribute__((used)) static int cmd_load_pcap(char *file)
{
	char *file_trim, *tmp;

	file_trim = strtok_r(file, " ", &tmp);
	if (file_trim == NULL)
		return CMD_ERR;

	try_close_pcap();

	return try_load_pcap(file_trim);
}