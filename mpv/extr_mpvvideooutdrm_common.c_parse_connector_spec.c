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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int atoi (char const*) ; 
 char* strchr (char const*,char) ; 
 char* talloc_strdup (struct mp_log*,char const*) ; 

__attribute__((used)) static void parse_connector_spec(struct mp_log *log,
                                 const char *connector_spec,
                                 int *card_no, char **connector_name)
{
    if (!connector_spec) {
        *card_no = 0;
        *connector_name = NULL;
        return;
    }
    char *dot_ptr = strchr(connector_spec, '.');
    if (dot_ptr) {
        *card_no = atoi(connector_spec);
        *connector_name = talloc_strdup(log, dot_ptr + 1);
    } else {
        *card_no = 0;
        *connector_name = talloc_strdup(log, connector_spec);
    }
}