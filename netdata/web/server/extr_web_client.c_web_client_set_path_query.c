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
struct web_client {size_t url_path_length; char* url_search_path; } ;

/* Variables and functions */

__attribute__((used)) static void web_client_set_path_query(struct web_client *w, char *s, char *ptr) {
    w->url_path_length = (size_t)(ptr -s);

    w->url_search_path = ptr;
}