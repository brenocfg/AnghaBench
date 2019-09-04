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
struct fscache_objlist_data {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 

__attribute__((used)) static void fscache_objlist_config(struct fscache_objlist_data *data)
{
#ifdef CONFIG_KEYS
	const struct user_key_payload *confkey;
	unsigned long config;
	struct key *key;
	const char *buf;
	int len;

	key = request_key(&key_type_user, "fscache:objlist", NULL);
	if (IS_ERR(key))
		goto no_config;

	config = 0;
	rcu_read_lock();

	confkey = user_key_payload_rcu(key);
	if (!confkey) {
		/* key was revoked */
		rcu_read_unlock();
		key_put(key);
		goto no_config;
	}

	buf = confkey->data;

	for (len = confkey->datalen - 1; len >= 0; len--) {
		switch (buf[len]) {
		case 'K': config |= FSCACHE_OBJLIST_CONFIG_KEY;		break;
		case 'A': config |= FSCACHE_OBJLIST_CONFIG_AUX;		break;
		case 'C': config |= FSCACHE_OBJLIST_CONFIG_COOKIE;	break;
		case 'c': config |= FSCACHE_OBJLIST_CONFIG_NOCOOKIE;	break;
		case 'B': config |= FSCACHE_OBJLIST_CONFIG_BUSY;	break;
		case 'b': config |= FSCACHE_OBJLIST_CONFIG_IDLE;	break;
		case 'W': config |= FSCACHE_OBJLIST_CONFIG_PENDWR;	break;
		case 'w': config |= FSCACHE_OBJLIST_CONFIG_NOPENDWR;	break;
		case 'R': config |= FSCACHE_OBJLIST_CONFIG_READS;	break;
		case 'r': config |= FSCACHE_OBJLIST_CONFIG_NOREADS;	break;
		case 'S': config |= FSCACHE_OBJLIST_CONFIG_WORK;	break;
		case 's': config |= FSCACHE_OBJLIST_CONFIG_NOWORK;	break;
		}
	}

	rcu_read_unlock();
	key_put(key);

	if (!(config & (FSCACHE_OBJLIST_CONFIG_COOKIE | FSCACHE_OBJLIST_CONFIG_NOCOOKIE)))
	    config   |= FSCACHE_OBJLIST_CONFIG_COOKIE | FSCACHE_OBJLIST_CONFIG_NOCOOKIE;
	if (!(config & (FSCACHE_OBJLIST_CONFIG_BUSY | FSCACHE_OBJLIST_CONFIG_IDLE)))
	    config   |= FSCACHE_OBJLIST_CONFIG_BUSY | FSCACHE_OBJLIST_CONFIG_IDLE;
	if (!(config & (FSCACHE_OBJLIST_CONFIG_PENDWR | FSCACHE_OBJLIST_CONFIG_NOPENDWR)))
	    config   |= FSCACHE_OBJLIST_CONFIG_PENDWR | FSCACHE_OBJLIST_CONFIG_NOPENDWR;
	if (!(config & (FSCACHE_OBJLIST_CONFIG_READS | FSCACHE_OBJLIST_CONFIG_NOREADS)))
	    config   |= FSCACHE_OBJLIST_CONFIG_READS | FSCACHE_OBJLIST_CONFIG_NOREADS;
	if (!(config & (FSCACHE_OBJLIST_CONFIG_EVENTS | FSCACHE_OBJLIST_CONFIG_NOEVENTS)))
	    config   |= FSCACHE_OBJLIST_CONFIG_EVENTS | FSCACHE_OBJLIST_CONFIG_NOEVENTS;
	if (!(config & (FSCACHE_OBJLIST_CONFIG_WORK | FSCACHE_OBJLIST_CONFIG_NOWORK)))
	    config   |= FSCACHE_OBJLIST_CONFIG_WORK | FSCACHE_OBJLIST_CONFIG_NOWORK;

	data->config = config;
	return;

no_config:
#endif
	data->config = ULONG_MAX;
}