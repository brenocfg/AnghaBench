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
struct lpm_mt_test_info {int iter; int map_fd; TYPE_1__* key; } ;
struct TYPE_2__ {int prefixlen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_lpm_mt_test_info(struct lpm_mt_test_info *info, int map_fd)
{
	info->iter = 2000;
	info->map_fd = map_fd;
	info->key[0].prefixlen = 16;
	inet_pton(AF_INET, "192.168.0.0", &info->key[0].data);
	info->key[1].prefixlen = 24;
	inet_pton(AF_INET, "192.168.0.0", &info->key[1].data);
	info->key[2].prefixlen = 24;
	inet_pton(AF_INET, "192.168.128.0", &info->key[2].data);
	info->key[3].prefixlen = 24;
	inet_pton(AF_INET, "192.168.1.0", &info->key[3].data);
}