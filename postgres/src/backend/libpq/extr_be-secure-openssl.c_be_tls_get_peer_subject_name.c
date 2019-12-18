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
struct TYPE_3__ {scalar_t__ peer; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  X509_NAME_to_cstring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_subject_name (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

void
be_tls_get_peer_subject_name(Port *port, char *ptr, size_t len)
{
	if (port->peer)
		strlcpy(ptr, X509_NAME_to_cstring(X509_get_subject_name(port->peer)), len);
	else
		ptr[0] = '\0';
}