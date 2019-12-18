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
struct userdata {char* url; int depth; } ;
struct slre_cap {int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; } ;
struct mg_connection {int /*<<< orphan*/  mgr; scalar_t__ user_data; } ;
struct TYPE_2__ {char* p; } ;
struct http_message {TYPE_1__ body; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLRE_IGNORE_CASE ; 
 int /*<<< orphan*/  crawl_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ max_depth ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  regex ; 
 int slre_match (int /*<<< orphan*/ ,char const*,int,struct slre_cap*,int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

void handle_reply(struct mg_connection *nc, struct http_message *hm) {
  struct userdata *ud = (struct userdata *) nc->user_data;
  const char *body = hm->body.p;

  int offset, max_matches = 2, cursor = 0, str_len = strlen(body);
  struct slre_cap caps[max_matches];

  printf("Loaded url: %s at depth %d\n", ud->url, ud->depth);
  if (ud->depth == max_depth) {
    return;
  }

  while (cursor < str_len &&
         (offset = slre_match(regex, body + cursor, str_len - cursor, caps,
                              max_matches, SLRE_IGNORE_CASE)) > 0) {
    crawl_page(nc->mgr, caps[0].ptr, caps[0].len, ud->depth + 1);
    cursor += offset;
  }
}