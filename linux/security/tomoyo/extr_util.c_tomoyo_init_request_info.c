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
typedef  int /*<<< orphan*/  u8 ;
struct tomoyo_request_info {int mode; int /*<<< orphan*/  type; int /*<<< orphan*/  profile; struct tomoyo_domain_info* domain; } ;
struct tomoyo_domain_info {int /*<<< orphan*/  ns; int /*<<< orphan*/  profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tomoyo_request_info*,int /*<<< orphan*/ ,int) ; 
 struct tomoyo_domain_info* tomoyo_domain () ; 
 int tomoyo_get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

int tomoyo_init_request_info(struct tomoyo_request_info *r,
			     struct tomoyo_domain_info *domain, const u8 index)
{
	u8 profile;

	memset(r, 0, sizeof(*r));
	if (!domain)
		domain = tomoyo_domain();
	r->domain = domain;
	profile = domain->profile;
	r->profile = profile;
	r->type = index;
	r->mode = tomoyo_get_mode(domain->ns, profile, index);
	return r->mode;
}