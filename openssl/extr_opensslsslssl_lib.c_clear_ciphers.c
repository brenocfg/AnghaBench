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
struct TYPE_4__ {int /*<<< orphan*/  write_hash; int /*<<< orphan*/  read_hash; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ssl_clear_cipher_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  ssl_clear_hash_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_ciphers(SSL *s)
{
    /* clear the current cipher */
    ssl_clear_cipher_ctx(s);
    ssl_clear_hash_ctx(&s->read_hash);
    ssl_clear_hash_ctx(&s->write_hash);
}