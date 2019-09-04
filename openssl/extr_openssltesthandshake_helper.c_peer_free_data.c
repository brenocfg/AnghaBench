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
struct TYPE_3__ {int /*<<< orphan*/  read_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ PEER ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void peer_free_data(PEER *peer)
{
    SSL_free(peer->ssl);
    OPENSSL_free(peer->write_buf);
    OPENSSL_free(peer->read_buf);
}