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
struct TYPE_4__ {scalar_t__ ssl_version; scalar_t__ session_id_length; int /*<<< orphan*/  session_id; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ssl_session_cmp(const SSL_SESSION *a, const SSL_SESSION *b)
{
    if (a->ssl_version != b->ssl_version)
        return 1;
    if (a->session_id_length != b->session_id_length)
        return 1;
    return memcmp(a->session_id, b->session_id, a->session_id_length);
}