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
struct mg_cgi_env_block {int dummy; } ;

/* Variables and functions */
 char* getenv (char const*) ; 
 int /*<<< orphan*/  mg_addenv (struct mg_cgi_env_block*,char*,char const*,char const*) ; 

__attribute__((used)) static void mg_addenv2(struct mg_cgi_env_block *blk, const char *name) {
  const char *s;
  if ((s = getenv(name)) != NULL) mg_addenv(blk, "%s=%s", name, s);
}