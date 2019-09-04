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
struct TYPE_3__ {int /*<<< orphan*/  rwstate; int /*<<< orphan*/  wbio; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 scalar_t__ BIO_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_WRITING ; 

int statem_flush(SSL *s)
{
    s->rwstate = SSL_WRITING;
    if (BIO_flush(s->wbio) <= 0) {
        return 0;
    }
    s->rwstate = SSL_NOTHING;

    return 1;
}