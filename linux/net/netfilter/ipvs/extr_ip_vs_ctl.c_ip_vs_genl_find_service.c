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
struct nlattr {int dummy; } ;
struct netns_ipvs {int dummy; } ;
struct ip_vs_service_user_kern {int dummy; } ;
struct ip_vs_service {int dummy; } ;

/* Variables and functions */
 struct ip_vs_service* ERR_PTR (int) ; 
 int ip_vs_genl_parse_service (struct netns_ipvs*,struct ip_vs_service_user_kern*,struct nlattr*,int,struct ip_vs_service**) ; 

__attribute__((used)) static struct ip_vs_service *ip_vs_genl_find_service(struct netns_ipvs *ipvs,
						     struct nlattr *nla)
{
	struct ip_vs_service_user_kern usvc;
	struct ip_vs_service *svc;
	int ret;

	ret = ip_vs_genl_parse_service(ipvs, &usvc, nla, false, &svc);
	return ret ? ERR_PTR(ret) : svc;
}