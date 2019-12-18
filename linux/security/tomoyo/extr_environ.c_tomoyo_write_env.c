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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct tomoyo_env_acl {int /*<<< orphan*/  env; TYPE_1__ head; } ;
struct tomoyo_acl_param {int dummy; } ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TOMOYO_TYPE_ENV_ACL ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  tomoyo_correct_word (char const*) ; 
 int /*<<< orphan*/  tomoyo_get_name (char const*) ; 
 int /*<<< orphan*/  tomoyo_put_name (int /*<<< orphan*/ ) ; 
 char* tomoyo_read_token (struct tomoyo_acl_param*) ; 
 int /*<<< orphan*/  tomoyo_same_env_acl ; 
 int tomoyo_update_domain (TYPE_1__*,int,struct tomoyo_acl_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tomoyo_write_env(struct tomoyo_acl_param *param)
{
	struct tomoyo_env_acl e = { .head.type = TOMOYO_TYPE_ENV_ACL };
	int error = -ENOMEM;
	const char *data = tomoyo_read_token(param);

	if (!tomoyo_correct_word(data) || strchr(data, '='))
		return -EINVAL;
	e.env = tomoyo_get_name(data);
	if (!e.env)
		return error;
	error = tomoyo_update_domain(&e.head, sizeof(e), param,
				  tomoyo_same_env_acl, NULL);
	tomoyo_put_name(e.env);
	return error;
}