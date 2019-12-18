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
struct TYPE_3__ {int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ SSL_pending (int /*<<< orphan*/ ) ; 

bool
pgtls_read_pending(PGconn *conn)
{
	return SSL_pending(conn->ssl) > 0;
}