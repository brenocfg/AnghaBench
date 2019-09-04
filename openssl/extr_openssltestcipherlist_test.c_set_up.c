#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* test_case_name; struct TYPE_7__* client; struct TYPE_7__* server; } ;
typedef  TYPE_1__ CIPHERLIST_TEST_FIXTURE ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 
 TYPE_1__* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  TLS_server_method () ; 
 int /*<<< orphan*/  tear_down (TYPE_1__*) ; 

__attribute__((used)) static CIPHERLIST_TEST_FIXTURE *set_up(const char *const test_case_name)
{
    CIPHERLIST_TEST_FIXTURE *fixture;

    if (!TEST_ptr(fixture = OPENSSL_zalloc(sizeof(*fixture))))
        return NULL;
    fixture->test_case_name = test_case_name;
    if (!TEST_ptr(fixture->server = SSL_CTX_new(TLS_server_method()))
            || !TEST_ptr(fixture->client = SSL_CTX_new(TLS_client_method()))) {
        tear_down(fixture);
        return NULL;
    }
    return fixture;
}