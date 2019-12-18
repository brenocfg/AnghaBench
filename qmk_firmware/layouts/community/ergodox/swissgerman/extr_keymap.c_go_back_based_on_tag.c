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

/* Variables and functions */
 int /*<<< orphan*/  KC_LEFT ; 
 int /*<<< orphan*/  send_key (int /*<<< orphan*/ ) ; 
 int const strlen (char*) ; 

void go_back_based_on_tag(char* tag) {
  const int BRACKETS_AND_SLASH_LENGTH = 3;

  for (int i=0; i < strlen(tag) + BRACKETS_AND_SLASH_LENGTH; i++) {
    send_key(KC_LEFT);
  }
}