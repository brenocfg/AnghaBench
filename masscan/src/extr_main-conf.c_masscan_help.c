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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
masscan_help()
{
    printf(
"MASSCAN is a fast port scanner. The primary input parameters are the\n"
"IP addresses/ranges you want to scan, and the port numbers. An example\n"
"is the following, which scans the 10.x.x.x network for web servers:\n"
" masscan 10.0.0.0/8 -p80\n"
"The program auto-detects network interface/adapter settings. If this\n"
"fails, you'll have to set these manually. The following is an\n"
"example of all the parameters that are needed:\n"
" --adapter-ip 192.168.10.123\n"
" --adapter-mac 00-11-22-33-44-55\n"
" --router-mac 66-55-44-33-22-11\n"
"Parameters can be set either via the command-line or config-file. The\n"
"names are the same for both. Thus, the above adapter settings would\n"
"appear as follows in a configuration file:\n"
" adapter-ip = 192.168.10.123\n"
" adapter-mac = 00-11-22-33-44-55\n"
" router-mac = 66-55-44-33-22-11\n"
"All single-dash parameters have a spelled out double-dash equivalent,\n"
"so '-p80' is the same as '--ports 80' (or 'ports = 80' in config file).\n"
"To use the config file, type:\n"
" masscan -c <filename>\n"
"To generate a config-file from the current settings, use the --echo\n"
"option. This stops the program from actually running, and just echoes\n"
"the current configuration instead. This is a useful way to generate\n"
"your first config file, or see a list of parameters you didn't know\n"
"about. I suggest you try it now:\n"
" masscan -p1234 --echo\n");
    exit(1);
}