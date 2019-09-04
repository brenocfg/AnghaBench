#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtmp_custom {char const* server; } ;

/* Variables and functions */

__attribute__((used)) static const char *rtmp_custom_url(void *data)
{
	struct rtmp_custom *service = data;
	return service->server;
}