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
struct TYPE_2__ {int inited; int /*<<< orphan*/  ctx_j; void* print_level; int /*<<< orphan*/  sock; int /*<<< orphan*/  zctx; } ;

/* Variables and functions */
 void* CLOUDLOG_DEBUG ; 
 void* CLOUDLOG_INFO ; 
 void* CLOUDLOG_WARNING ; 
 char* COMMA_VERSION ; 
 int /*<<< orphan*/  ZMQ_PUSH ; 
 int /*<<< orphan*/  cloudlog_bind_locked (char*,char*) ; 
 void* getenv (char*) ; 
 int /*<<< orphan*/  json_append_member (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_mkbool (int) ; 
 int /*<<< orphan*/  json_mkobject () ; 
 TYPE_1__ s ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  zmq_connect (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmq_ctx_new () ; 
 int /*<<< orphan*/  zmq_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cloudlog_init() {
  if (s.inited) return;
  s.ctx_j = json_mkobject();
  s.zctx = zmq_ctx_new();
  s.sock = zmq_socket(s.zctx, ZMQ_PUSH);
  zmq_connect(s.sock, "ipc:///tmp/logmessage");

  s.print_level = CLOUDLOG_WARNING;
  const char* print_level = getenv("LOGPRINT");
  if (print_level) {
    if (strcmp(print_level, "debug") == 0) {
      s.print_level = CLOUDLOG_DEBUG;
    } else if (strcmp(print_level, "info") == 0) {
      s.print_level = CLOUDLOG_INFO;
    } else if (strcmp(print_level, "warning") == 0) {
      s.print_level = CLOUDLOG_WARNING;
    }
  }

  // openpilot bindings
  char* dongle_id = getenv("DONGLE_ID");
  if (dongle_id) {
    cloudlog_bind_locked("dongle_id", dongle_id);
  }
  cloudlog_bind_locked("version", COMMA_VERSION);
  bool dirty = !getenv("CLEAN");
  json_append_member(s.ctx_j, "dirty", json_mkbool(dirty));

  s.inited = true;
}