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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct web_client {int flags; TYPE_1__ response; } ;

/* Variables and functions */
 size_t MAX_HEADERS ; 
 int WEB_CLIENT_FLAG_WAIT_RECEIVE ; 
 int /*<<< orphan*/  assert_int_equal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_request (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  post_test_cleanup (struct web_client*) ; 
 struct web_client* pre_test_setup () ; 
 int /*<<< orphan*/  web_client_process_request (struct web_client*) ; 

__attribute__((used)) static void api_info(void **state)
{
    for (size_t i = 0; i < MAX_HEADERS; i++) {
        struct web_client *w = pre_test_setup();
        build_request(w->response.data, "/api/v1/info", true, i);
        web_client_process_request(w);
        assert_int_equal(w->flags & WEB_CLIENT_FLAG_WAIT_RECEIVE, 0);
        post_test_cleanup(w);
    }
}