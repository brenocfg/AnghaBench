#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  encoding; } ;

/* Variables and functions */
 TYPE_1__* ClientEncoding ; 
 char* pg_any_to_server (char const*,int,int /*<<< orphan*/ ) ; 

char *
pg_client_to_server(const char *s, int len)
{
	return pg_any_to_server(s, len, ClientEncoding->encoding);
}