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
struct mg_connection {int dummy; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  dst ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  MG_EV_ACCEPT 132 
#define  MG_EV_CLOSE 131 
#define  MG_EV_CONNECT 130 
#define  MG_EV_RECV 129 
#define  MG_EV_SEND 128 
 int MG_SOCK_STRINGIFY_IP ; 
 int MG_SOCK_STRINGIFY_PORT ; 
 int MG_SOCK_STRINGIFY_REMOTE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned long,void*,char*,char const*,char*,int) ; 
 int /*<<< orphan*/  mg_conn_addr_to_str (struct mg_connection*,char*,int,int) ; 
 int /*<<< orphan*/ * mg_fopen (char const*,char*) ; 
 int /*<<< orphan*/  mg_hexdumpf (int /*<<< orphan*/ *,void const*,int) ; 
 scalar_t__ mg_time () ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 

void mg_hexdump_connection(struct mg_connection *nc, const char *path,
                           const void *buf, int num_bytes, int ev) {
  FILE *fp = NULL;
  char src[60], dst[60];
  const char *tag = NULL;
  switch (ev) {
    case MG_EV_RECV:
      tag = "<-";
      break;
    case MG_EV_SEND:
      tag = "->";
      break;
    case MG_EV_ACCEPT:
      tag = "<A";
      break;
    case MG_EV_CONNECT:
      tag = "C>";
      break;
    case MG_EV_CLOSE:
      tag = "XX";
      break;
  }
  if (tag == NULL) return; /* Don't log MG_EV_TIMER, etc */

  if (strcmp(path, "-") == 0) {
    fp = stdout;
  } else if (strcmp(path, "--") == 0) {
    fp = stderr;
#if MG_ENABLE_FILESYSTEM
  } else {
    fp = mg_fopen(path, "a");
#endif
  }
  if (fp == NULL) return;

  mg_conn_addr_to_str(nc, src, sizeof(src),
                      MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
  mg_conn_addr_to_str(nc, dst, sizeof(dst), MG_SOCK_STRINGIFY_IP |
                                                MG_SOCK_STRINGIFY_PORT |
                                                MG_SOCK_STRINGIFY_REMOTE);
  fprintf(fp, "%lu %p %s %s %s %d\n", (unsigned long) mg_time(), (void *) nc,
          src, tag, dst, (int) num_bytes);
  if (num_bytes > 0) {
    mg_hexdumpf(fp, buf, num_bytes);
  }
  if (fp != stdout && fp != stderr) fclose(fp);
}