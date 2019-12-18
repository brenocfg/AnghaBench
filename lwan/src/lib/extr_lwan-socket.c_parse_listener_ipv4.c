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
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 scalar_t__ streq (char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static sa_family_t parse_listener_ipv4(char *listener, char **node, char **port)
{
    char *colon = strrchr(listener, ':');
    if (!colon) {
        *port = "8080";
        if (!strchr(listener, '.')) {
            /* 8080 */
            *node = "0.0.0.0";
        } else {
            /* 127.0.0.1 */
            *node = listener;
        }
    } else {
        /*
         * 127.0.0.1:8080
         * localhost:8080
         */
        *colon = '\0';
        *node = listener;
        *port = colon + 1;

        if (streq(*node, "*")) {
            /* *:8080 */
            *node = "0.0.0.0";
        }
    }

    return AF_INET;
}