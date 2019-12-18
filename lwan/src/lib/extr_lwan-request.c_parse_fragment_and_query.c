#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* value; size_t len; } ;
struct lwan_request_parser_helper {TYPE_2__ query_string; } ;
struct TYPE_3__ {char* value; size_t len; } ;
struct lwan_request {TYPE_1__ url; struct lwan_request_parser_helper* helper; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int /*<<< orphan*/ ) ; 
 char* memchr (char*,char,size_t) ; 
 char* memrchr (char*,char,size_t) ; 

__attribute__((used)) static void parse_fragment_and_query(struct lwan_request *request,
                                     const char *space)
{
    struct lwan_request_parser_helper *helper = request->helper;

    /* Fragments shouldn't be received by the server, but look for them anyway
     * just in case. */
    char *fragment = memrchr(request->url.value, '#', request->url.len);
    if (UNLIKELY(fragment != NULL)) {
        *fragment = '\0';
        request->url.len = (size_t)(fragment - request->url.value);
        space = fragment;
    }

    char *query_string = memchr(request->url.value, '?', request->url.len);
    if (query_string) {
        *query_string = '\0';
        helper->query_string.value = query_string + 1;
        helper->query_string.len = (size_t)(space - query_string - 1);
        request->url.len -= helper->query_string.len + 1;
    }
}