#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct listening_socket_s {scalar_t__ refcount; int const type; int /*<<< orphan*/  key; int /*<<< orphan*/  sock; } ;
struct fpm_worker_pool_s {int listen_address_domain; int listening_socket; int /*<<< orphan*/  scoreboard; struct fpm_worker_pool_s* next; } ;
struct TYPE_4__ {unsigned int used; struct listening_socket_s* data; } ;

/* Variables and functions */
#define  FPM_AF_INET 129 
#define  FPM_AF_UNIX 128 
 int /*<<< orphan*/  FPM_CLEANUP_ALL ; 
 unsigned int FPM_ENV_SOCKET_SET_MAX ; 
 int /*<<< orphan*/  FPM_SCOREBOARD_ACTION_SET ; 
 int /*<<< orphan*/  FPM_STORE_SOCKET ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_array_init (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  fpm_array_item_remove (TYPE_1__*,unsigned int) ; 
 scalar_t__ fpm_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_scoreboard_update (int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fpm_socket_af_inet_listening_socket (struct fpm_worker_pool_s*) ; 
 int fpm_socket_af_unix_listening_socket (struct fpm_worker_pool_s*) ; 
 scalar_t__ fpm_socket_get_listening_queue (int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  fpm_sockets_cleanup ; 
 int fpm_sockets_domain_from_address (char*) ; 
 int /*<<< orphan*/  fpm_sockets_hash_op (int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_unix_resolve_socket_premissions (struct fpm_worker_pool_s*) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_1__ sockets_list ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int,char*) ; 

int fpm_sockets_init_main() /* {{{ */
{
	unsigned i, lq_len;
	struct fpm_worker_pool_s *wp;
	char sockname[32];
	char sockpath[256];
	char *inherited;
	struct listening_socket_s *ls;

	if (0 == fpm_array_init(&sockets_list, sizeof(struct listening_socket_s), 10)) {
		return -1;
	}

	/* import inherited sockets */
	for (i = 0; i < FPM_ENV_SOCKET_SET_MAX; i++) {
		if (!i) {
			strcpy(sockname, "FPM_SOCKETS");
		} else {
			sprintf(sockname, "FPM_SOCKETS_%d", i);
		}
		inherited = getenv(sockname);
		if (!inherited) {
			break;
		}

		while (inherited && *inherited) {
			char *comma = strchr(inherited, ',');
			int type, fd_no;
			char *eq;

			if (comma) {
				*comma = '\0';
			}

			eq = strchr(inherited, '=');
			if (eq) {
				int sockpath_len = eq - inherited;
				if (sockpath_len > 255) {
					/* this should never happen as UDS limit is lower */
					sockpath_len = 255;
				}
				memcpy(sockpath, inherited, sockpath_len);
				sockpath[sockpath_len] = '\0';
				fd_no = atoi(eq + 1);
				type = fpm_sockets_domain_from_address(sockpath);
				zlog(ZLOG_NOTICE, "using inherited socket fd=%d, \"%s\"", fd_no, sockpath);
				fpm_sockets_hash_op(fd_no, 0, sockpath, type, FPM_STORE_SOCKET);
			}

			if (comma) {
				inherited = comma + 1;
			} else {
				inherited = 0;
			}
		}
	}

	/* create all required sockets */
	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		switch (wp->listen_address_domain) {
			case FPM_AF_INET :
				wp->listening_socket = fpm_socket_af_inet_listening_socket(wp);
				break;

			case FPM_AF_UNIX :
				if (0 > fpm_unix_resolve_socket_premissions(wp)) {
					return -1;
				}
				wp->listening_socket = fpm_socket_af_unix_listening_socket(wp);
				break;
		}

		if (wp->listening_socket == -1) {
			return -1;
		}

	if (wp->listen_address_domain == FPM_AF_INET && fpm_socket_get_listening_queue(wp->listening_socket, NULL, &lq_len) >= 0) {
			fpm_scoreboard_update(-1, -1, -1, (int)lq_len, -1, -1, 0, FPM_SCOREBOARD_ACTION_SET, wp->scoreboard);
		}
	}

	/* close unused sockets that was inherited */
	ls = sockets_list.data;

	for (i = 0; i < sockets_list.used; ) {
		if (ls->refcount == 0) {
			close(ls->sock);
			if (ls->type == FPM_AF_UNIX) {
				unlink(ls->key);
			}
			free(ls->key);
			fpm_array_item_remove(&sockets_list, i);
		} else {
			++i;
			++ls;
		}
	}

	if (0 > fpm_cleanup_add(FPM_CLEANUP_ALL, fpm_sockets_cleanup, 0)) {
		return -1;
	}
	return 0;
}