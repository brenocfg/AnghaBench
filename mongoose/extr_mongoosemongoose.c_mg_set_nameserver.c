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
struct mg_mgr {int /*<<< orphan*/ * nameserver; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_FREE (char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

void mg_set_nameserver(struct mg_mgr *mgr, const char *nameserver) {
  MG_FREE((char *) mgr->nameserver);
  mgr->nameserver = NULL;
  if (nameserver != NULL) {
    mgr->nameserver = strdup(nameserver);
  }
}