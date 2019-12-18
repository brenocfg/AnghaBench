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
struct mg_mgr {int dummy; } ;
struct mg_iface_vtable {int dummy; } ;
struct mg_iface {struct mg_iface_vtable const* vtable; int /*<<< orphan*/ * data; struct mg_mgr* mgr; } ;

/* Variables and functions */
 scalar_t__ MG_CALLOC (int,int) ; 

struct mg_iface *mg_if_create_iface(const struct mg_iface_vtable *vtable,
                                    struct mg_mgr *mgr) {
  struct mg_iface *iface = (struct mg_iface *) MG_CALLOC(1, sizeof(*iface));
  iface->mgr = mgr;
  iface->data = NULL;
  iface->vtable = vtable;
  return iface;
}