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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void show_usage_and_exit(const char *prog_name) {
  fprintf(stderr, "%s\n", "Copyright (c) Cesanta. Built on: " __DATE__);
  fprintf(stderr, "Usage: %s [OPTIONS] [IP:]PORT\n", prog_name);
  fprintf(stderr, "%s\n", "Options:");
  fprintf(stderr, "%s\n", "  -l\t\tOpen a listening socket");
  fprintf(stderr, "%s\n", "  -d file\tHexdump traffic into a file");
  fprintf(stderr, "%s\n", "  -ws\t\tUse WebSocket protocol");
  exit(EXIT_FAILURE);
}