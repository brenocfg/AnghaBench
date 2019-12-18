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
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static sa_family_t parse_listener_ipv6(char *listener, char **node, char **port)
{
    char *last_colon = strrchr(listener, ':');
    if (!last_colon)
        return AF_UNSPEC;

    if (*(last_colon - 1) == ']') {
        /* [::]:8080 */
        *(last_colon - 1) = '\0';
        *node = listener + 1;
        *port = last_colon + 1;
    } else {
        /* [::1] */
        listener[strlen(listener) - 1] = '\0';
        *node = listener + 1;
        *port = "8080";
    }

    return AF_INET6;
}