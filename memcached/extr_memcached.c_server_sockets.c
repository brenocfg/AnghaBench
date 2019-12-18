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
typedef  enum network_transport { ____Placeholder_network_transport } network_transport ;
struct TYPE_2__ {int ssl_enabled; char* inter; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  safe_strtol (char*,int*) ; 
 int server_socket (char*,int,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,scalar_t__) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int server_sockets(int port, enum network_transport transport,
                          FILE *portnumber_file) {
    bool ssl_enabled = false;

#ifdef TLS
    const char *notls = "notls";
    ssl_enabled = settings.ssl_enabled;
#endif

    if (settings.inter == NULL) {
        return server_socket(settings.inter, port, transport, portnumber_file, ssl_enabled);
    } else {
        // tokenize them and bind to each one of them..
        char *b;
        int ret = 0;
        char *list = strdup(settings.inter);

        if (list == NULL) {
            fprintf(stderr, "Failed to allocate memory for parsing server interface string\n");
            return 1;
        }
        for (char *p = strtok_r(list, ";,", &b);
            p != NULL;
            p = strtok_r(NULL, ";,", &b)) {
            int the_port = port;
#ifdef TLS
            ssl_enabled = settings.ssl_enabled;
            // "notls" option is valid only when memcached is run with SSL enabled.
            if (strncmp(p, notls, strlen(notls)) == 0) {
                if (!settings.ssl_enabled) {
                    fprintf(stderr, "'notls' option is valid only when SSL is enabled\n");
                    return 1;
                }
                ssl_enabled = false;
                p += strlen(notls) + 1;
            }
#endif

            char *h = NULL;
            if (*p == '[') {
                // expecting it to be an IPv6 address enclosed in []
                // i.e. RFC3986 style recommended by RFC5952
                char *e = strchr(p, ']');
                if (e == NULL) {
                    fprintf(stderr, "Invalid IPV6 address: \"%s\"", p);
                    free(list);
                    return 1;
                }
                h = ++p; // skip the opening '['
                *e = '\0';
                p = ++e; // skip the closing ']'
            }

            char *s = strchr(p, ':');
            if (s != NULL) {
                // If no more semicolons - attempt to treat as port number.
                // Otherwise the only valid option is an unenclosed IPv6 without port, until
                // of course there was an RFC3986 IPv6 address previously specified -
                // in such a case there is no good option, will just send it to fail as port number.
                if (strchr(s + 1, ':') == NULL || h != NULL) {
                    *s = '\0';
                    ++s;
                    if (!safe_strtol(s, &the_port)) {
                        fprintf(stderr, "Invalid port number: \"%s\"", s);
                        free(list);
                        return 1;
                    }
                }
            }

            if (h != NULL)
                p = h;

            if (strcmp(p, "*") == 0) {
                p = NULL;
            }
            ret |= server_socket(p, the_port, transport, portnumber_file, ssl_enabled);
        }
        free(list);
        return ret;
    }
}