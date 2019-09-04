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
struct mg_connection {int dummy; } ;
struct http_message {int /*<<< orphan*/  body; } ;
struct TYPE_2__ {int /*<<< orphan*/  setting2; int /*<<< orphan*/  setting1; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_get_http_var (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_http_send_redirect (struct mg_connection*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mk_str (char*) ; 
 TYPE_1__ s_settings ; 

__attribute__((used)) static void handle_save(struct mg_connection *nc, struct http_message *hm) {
  // Get form variables and store settings values
  mg_get_http_var(&hm->body, "setting1", s_settings.setting1,
                  sizeof(s_settings.setting1));
  mg_get_http_var(&hm->body, "setting2", s_settings.setting2,
                  sizeof(s_settings.setting2));

  // Send response
  mg_http_send_redirect(nc, 302, mg_mk_str("/"), mg_mk_str(NULL));
}