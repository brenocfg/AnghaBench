#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t master_key_length; int /*<<< orphan*/  master_key; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int SSL_SESSION_set1_master_key(SSL_SESSION *sess, const unsigned char *in,
                                size_t len)
{
    if (len > sizeof(sess->master_key))
        return 0;

    memcpy(sess->master_key, in, len);
    sess->master_key_length = len;
    return 1;
}