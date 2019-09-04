#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_un {char* sun_path; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct listening_socket_s {int refcount; int sock; int type; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {unsigned int used; struct listening_socket_s* data; } ;

/* Variables and functions */
#define  FPM_AF_INET 132 
#define  FPM_AF_UNIX 131 
#define  FPM_GET_USE_SOCKET 130 
#define  FPM_STORE_SOCKET 129 
#define  FPM_STORE_USE_SOCKET 128 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 struct listening_socket_s* fpm_array_push (TYPE_1__*) ; 
 int /*<<< orphan*/  fpm_get_in_addr (struct sockaddr*) ; 
 int fpm_get_in_port (struct sockaddr*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ sockets_list ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int fpm_sockets_hash_op(int sock, struct sockaddr *sa, char *key, int type, int op) /* {{{ */
{
	if (key == NULL) {
		switch (type) {
			case FPM_AF_INET : {
				key = alloca(INET6_ADDRSTRLEN+10);
				inet_ntop(sa->sa_family, fpm_get_in_addr(sa), key, INET6_ADDRSTRLEN);
				sprintf(key+strlen(key), ":%d", fpm_get_in_port(sa));
				break;
			}

			case FPM_AF_UNIX : {
				struct sockaddr_un *sa_un = (struct sockaddr_un *) sa;
				key = alloca(strlen(sa_un->sun_path) + 1);
				strcpy(key, sa_un->sun_path);
				break;
			}

			default :
				return -1;
		}
	}

	switch (op) {

		case FPM_GET_USE_SOCKET :
		{
			unsigned i;
			struct listening_socket_s *ls = sockets_list.data;

			for (i = 0; i < sockets_list.used; i++, ls++) {
				if (!strcmp(ls->key, key)) {
					++ls->refcount;
					return ls->sock;
				}
			}
			break;
		}

		case FPM_STORE_SOCKET :			/* inherited socket */
		case FPM_STORE_USE_SOCKET :		/* just created */
		{
			struct listening_socket_s *ls;

			ls = fpm_array_push(&sockets_list);
			if (!ls) {
				break;
			}

			if (op == FPM_STORE_SOCKET) {
				ls->refcount = 0;
			} else {
				ls->refcount = 1;
			}
			ls->type = type;
			ls->sock = sock;
			ls->key = strdup(key);

			return 0;
		}
	}
	return -1;
}