#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  client_random; } ;
struct TYPE_6__ {TYPE_1__ s3; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_RANDOM_SIZE ; 
 int nss_keylog_int (char const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int ssl_log_secret(SSL *ssl,
                   const char *label,
                   const uint8_t *secret,
                   size_t secret_len)
{
    return nss_keylog_int(label,
                          ssl,
                          ssl->s3.client_random,
                          SSL3_RANDOM_SIZE,
                          secret,
                          secret_len);
}