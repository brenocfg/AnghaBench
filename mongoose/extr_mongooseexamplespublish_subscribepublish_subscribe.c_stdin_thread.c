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
 int EOF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getchar () ; 
 scalar_t__ send (int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void *stdin_thread(void *param) {
  int ch, sock = *(int *) param;
  // Forward all types characters to the socketpair
  while ((ch = getchar()) != EOF) {
    unsigned char c = (unsigned char) ch;
    if (send(sock, (const char *) &c, 1, 0) < 0) {
      fprintf(stderr, "Failed to send byte to the socket");
    }
  }
  return NULL;
}