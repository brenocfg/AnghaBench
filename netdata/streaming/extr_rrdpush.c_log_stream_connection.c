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
 int /*<<< orphan*/  gettid () ; 
 int /*<<< orphan*/  log_access (char*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static void log_stream_connection(const char *client_ip, const char *client_port, const char *api_key, const char *machine_guid, const char *host, const char *msg) {
    log_access("STREAM: %d '[%s]:%s' '%s' host '%s' api key '%s' machine guid '%s'", gettid(), client_ip, client_port, msg, host, api_key, machine_guid);
}