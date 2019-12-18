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
struct TYPE_3__ {scalar_t__ ssl; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/ * SSL_get_current_compression (scalar_t__) ; 

bool
be_tls_get_compression(Port *port)
{
	if (port->ssl)
		return (SSL_get_current_compression(port->ssl) != NULL);
	else
		return false;
}