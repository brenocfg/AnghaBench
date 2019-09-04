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
struct key_value_s {char* key; scalar_t__ value; struct key_value_s* next; } ;
struct fpm_worker_pool_s {scalar_t__ home; scalar_t__ user; TYPE_1__* config; } ;
struct TYPE_2__ {struct key_value_s* env; scalar_t__ clear_env; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clearenv () ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  fpm_env_setproctitle (char*) ; 
 int /*<<< orphan*/  setenv (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fpm_env_init_child(struct fpm_worker_pool_s *wp) /* {{{ */
{
	struct key_value_s *kv;
	char *title;
	spprintf(&title, 0, "pool %s", wp->config->name);
	fpm_env_setproctitle(title);
	efree(title);

	if (wp->config->clear_env) {
		clearenv();
	}

	for (kv = wp->config->env; kv; kv = kv->next) {
		setenv(kv->key, kv->value, 1);
	}

	if (wp->user) {
		setenv("USER", wp->user, 1);
	}

	if (wp->home) {
		setenv("HOME", wp->home, 1);
	}

	return 0;
}