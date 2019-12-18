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
struct rtmp_common {char const* key; } ;

/* Variables and functions */

__attribute__((used)) static const char *rtmp_common_key(void *data)
{
	struct rtmp_common *service = data;
	return service->key;
}