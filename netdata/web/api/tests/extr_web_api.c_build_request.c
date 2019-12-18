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
struct web_buffer {int dummy; } ;

/* Variables and functions */
 size_t MAX_HEADERS ; 
 int /*<<< orphan*/  buffer_reset (struct web_buffer*) ; 
 int /*<<< orphan*/  buffer_strcat (struct web_buffer*,char const*) ; 
 char** http_headers ; 

__attribute__((used)) static void build_request(struct web_buffer *wb, const char *url, bool use_cr, size_t num_headers)
{
    buffer_reset(wb);
    buffer_strcat(wb, "GET ");
    buffer_strcat(wb, url);
    buffer_strcat(wb, " HTTP/1.1");
    if (use_cr)
        buffer_strcat(wb, "\r");
    buffer_strcat(wb, "\n");
    for (size_t i = 0; i < num_headers && i < MAX_HEADERS; i++) {
        buffer_strcat(wb, http_headers[i]);
        if (use_cr)
            buffer_strcat(wb, "\r");
        buffer_strcat(wb, "\n");
    }
    if (use_cr)
        buffer_strcat(wb, "\r");
    buffer_strcat(wb, "\n");
}