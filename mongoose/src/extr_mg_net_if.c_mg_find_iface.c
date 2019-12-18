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
struct mg_mgr {int num_ifaces; struct mg_iface** ifaces; } ;
struct mg_iface_vtable {int dummy; } ;
struct mg_iface {struct mg_iface_vtable const* vtable; } ;

/* Variables and functions */

struct mg_iface *mg_find_iface(struct mg_mgr *mgr,
                               const struct mg_iface_vtable *vtable,
                               struct mg_iface *from) {
  int i = 0;
  if (from != NULL) {
    for (i = 0; i < mgr->num_ifaces; i++) {
      if (mgr->ifaces[i] == from) {
        i++;
        break;
      }
    }
  }

  for (; i < mgr->num_ifaces; i++) {
    if (mgr->ifaces[i]->vtable == vtable) {
      return mgr->ifaces[i];
    }
  }
  return NULL;
}