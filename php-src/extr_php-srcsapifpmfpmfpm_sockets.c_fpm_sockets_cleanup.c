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
struct listening_socket_s {unsigned int sock; char* key; scalar_t__ type; } ;
struct TYPE_3__ {unsigned int used; struct listening_socket_s* data; } ;

/* Variables and functions */
 scalar_t__ FPM_AF_UNIX ; 
 int FPM_CLEANUP_PARENT_EXEC ; 
 int FPM_CLEANUP_PARENT_EXIT_MAIN ; 
 int FPM_ENV_SOCKET_SET_MAX ; 
 unsigned int FPM_ENV_SOCKET_SET_SIZE ; 
 int /*<<< orphan*/  close (unsigned int) ; 
 int /*<<< orphan*/  fpm_array_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* realloc (char*,scalar_t__) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 TYPE_1__ sockets_list ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void fpm_sockets_cleanup(int which, void *arg) /* {{{ */
{
	unsigned i;
	unsigned socket_set_count = 0;
	unsigned socket_set[FPM_ENV_SOCKET_SET_MAX];
	unsigned socket_set_buf = 0;
	char envname[32];
	char *env_value = 0;
	int p = 0;
	struct listening_socket_s *ls = sockets_list.data;

	for (i = 0; i < sockets_list.used; i++, ls++) {
		if (which != FPM_CLEANUP_PARENT_EXEC) {
			close(ls->sock);
		} else { /* on PARENT EXEC we want socket fds to be inherited through environment variable */
			char fd[32];
			sprintf(fd, "%d", ls->sock);

			socket_set_buf = (i % FPM_ENV_SOCKET_SET_SIZE == 0 && i) ? 1 : 0;
			env_value = realloc(env_value, p + (p ? 1 : 0) + strlen(ls->key) + 1 + strlen(fd) + socket_set_buf + 1);

			if (i % FPM_ENV_SOCKET_SET_SIZE == 0) {
				socket_set[socket_set_count] = p + socket_set_buf;
				socket_set_count++;
				if (i) {
					*(env_value + p + 1) = 0;
				}
			}

			p += sprintf(env_value + p + socket_set_buf, "%s%s=%s", (p && !socket_set_buf) ? "," : "", ls->key, fd);
			p += socket_set_buf;
		}

		if (which == FPM_CLEANUP_PARENT_EXIT_MAIN) {
			if (ls->type == FPM_AF_UNIX) {
				unlink(ls->key);
			}
		}
		free(ls->key);
	}

	if (env_value) {
		for (i = 0; i < socket_set_count; i++) {
			if (!i) {
				strcpy(envname, "FPM_SOCKETS");
			} else {
				sprintf(envname, "FPM_SOCKETS_%d", i);
			}
			setenv(envname, env_value + socket_set[i], 1);
		}
		free(env_value);
	}

	fpm_array_free(&sockets_list);
}