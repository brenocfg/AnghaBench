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
struct TYPE_4__ {int /*<<< orphan*/ * uri; } ;
typedef  TYPE_1__ uri_player ;

/* Variables and functions */
 TYPE_1__* players ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

uri_player* get_player_by_uri(const char* uri) {
  for (uri_player *s = players; s->uri != NULL; s++) {
    if (strcmp(s->uri, uri) == 0) {
      return s;
    }
  }

  return NULL;
}