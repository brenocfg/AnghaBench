#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_fragment_len_mode; int /*<<< orphan*/  ct_validation; int /*<<< orphan*/  alpn_protocols; int /*<<< orphan*/  npn_protocols; int /*<<< orphan*/  servername; int /*<<< orphan*/  verify_callback; } ;
typedef  TYPE_1__ SSL_TEST_CLIENT_CONF ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clientconf_eq(SSL_TEST_CLIENT_CONF *conf1,
                         SSL_TEST_CLIENT_CONF *conf2)
{
    if (!TEST_int_eq(conf1->verify_callback, conf2->verify_callback)
            || !TEST_int_eq(conf1->servername, conf2->servername)
            || !TEST_str_eq(conf1->npn_protocols, conf2->npn_protocols)
            || !TEST_str_eq(conf1->alpn_protocols, conf2->alpn_protocols)
            || !TEST_int_eq(conf1->ct_validation, conf2->ct_validation)
            || !TEST_int_eq(conf1->max_fragment_len_mode,
                            conf2->max_fragment_len_mode))
        return 0;
    return 1;
}