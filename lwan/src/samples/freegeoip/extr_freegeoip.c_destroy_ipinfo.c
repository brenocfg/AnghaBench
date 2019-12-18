#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct ip_info* area; struct ip_info* code; } ;
struct TYPE_6__ {struct ip_info* zip_code; struct ip_info* name; } ;
struct TYPE_5__ {struct ip_info* name; struct ip_info* code; } ;
struct TYPE_8__ {struct ip_info* name; struct ip_info* code; } ;
struct ip_info {struct ip_info* ip; TYPE_3__ metro; TYPE_2__ city; TYPE_1__ region; TYPE_4__ country; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ip_info*) ; 

__attribute__((used)) static void destroy_ipinfo(struct cache_entry *entry,
                           void *context __attribute__((unused)))
{
    struct ip_info *ip_info = (struct ip_info *)entry;

    if (!ip_info)
        return;

    free(ip_info->country.code);
    free(ip_info->country.name);
    free(ip_info->region.code);
    free(ip_info->region.name);
    free(ip_info->city.name);
    free(ip_info->city.zip_code);
    free(ip_info->metro.code);
    free(ip_info->metro.area);
    free(ip_info->ip);
    free(ip_info);
}