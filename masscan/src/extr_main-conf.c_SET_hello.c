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
struct Masscan {int is_hello_ssl; int is_hello_smbv1; int is_hello_http; scalar_t__ echo; } ;

/* Variables and functions */
 int CONF_ERR ; 
 int CONF_OK ; 
 scalar_t__ EQUALS (char*,char const*) ; 
 int /*<<< orphan*/  UNUSEDPARM (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int SET_hello(struct Masscan *masscan, const char *name, const char *value)
{
    UNUSEDPARM(name);
    if (masscan->echo) {
        if (masscan->is_hello_ssl) {
            fprintf(masscan->echo, "hello = ssl\n");
        } else if (masscan->is_hello_smbv1) {
            fprintf(masscan->echo, "hello = smbv1\n");
        } else if (masscan->is_hello_http) {
            fprintf(masscan->echo, "hello = http\n");
        }
        return 0;
    }
    if (EQUALS("ssl", value))
        masscan->is_hello_ssl = 1;
    else if (EQUALS("smbv1", value))
        masscan->is_hello_smbv1 = 1;
    else if (EQUALS("http", value))
        masscan->is_hello_http = 1;
    else {
        fprintf(stderr, "FAIL: %s: unknown hello type\n", value);
        return CONF_ERR;
    }
    return CONF_OK;
}