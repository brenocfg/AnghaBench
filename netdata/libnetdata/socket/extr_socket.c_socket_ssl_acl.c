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
typedef  int /*<<< orphan*/  WEB_CLIENT_ACL ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_CLIENT_ACL_NONE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_SSL_FORCE ; 
 int /*<<< orphan*/  WEB_CLIENT_ACL_SSL_OPTIONAL ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

WEB_CLIENT_ACL socket_ssl_acl(char *acl) {
    char *ssl = strchr(acl,'^');
    if(ssl) {
        //Due the format of the SSL command it is always the last command,
        //we finish it here to avoid problems with the ACLs
        *ssl = '\0';
#ifdef ENABLE_HTTPS
        ssl++;
        if (!strncmp("SSL=",ssl,4)) {
            ssl += 4;
            if (!strcmp(ssl,"optional")) {
                return WEB_CLIENT_ACL_SSL_OPTIONAL;
            }
            else if (!strcmp(ssl,"force")) {
                return WEB_CLIENT_ACL_SSL_FORCE;
            }
        }
#endif
    }

    return WEB_CLIENT_ACL_NONE;
}