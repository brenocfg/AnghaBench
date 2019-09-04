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
struct mg_iface {int /*<<< orphan*/  data; } ;
struct mg_ev_mgr_lwip_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_INFO ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWIP_VERSION_MAJOR ; 
 int /*<<< orphan*/  LWIP_VERSION_MINOR ; 
 int /*<<< orphan*/  LWIP_VERSION_REVISION ; 
 int /*<<< orphan*/  MG_CALLOC (int,int) ; 
 int /*<<< orphan*/  MG_VERSION ; 

void mg_lwip_if_init(struct mg_iface *iface) {
  LOG(LL_INFO, ("Mongoose %s, LwIP %u.%u.%u", MG_VERSION, LWIP_VERSION_MAJOR,
                LWIP_VERSION_MINOR, LWIP_VERSION_REVISION));
  iface->data = MG_CALLOC(1, sizeof(struct mg_ev_mgr_lwip_data));
}